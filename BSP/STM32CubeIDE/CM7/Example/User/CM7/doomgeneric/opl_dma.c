//
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2021-2022 Graham Sanderson
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//     OPL SDL interface.
//

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "stm32h7xx_hal.h"
#include "doomtype.h"

//#pragma GCC optimize("O3,inline")             // "inline" won't happen without it

#define AUDIO_SAMPLE_FREQ 49716
//#define TIMER_FREQ 10

#define USE_EMU8950_OPL 1

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#endif

#if USE_WOODY_OPL
#include "woody_opl.h"
#elif USE_EMU8950_OPL
#include "emu8950.h"
#else
#include "opl3.h"
#endif

#include "opl.h"
#include "opl_internal.h"

#include "opl_queue.h"

#define MAX_SOUND_SLICE_TIME 1 /* ms */

typedef struct
{
    unsigned int rate;        // Number of times the timer is advanced per sec.
    unsigned int enabled;     // Non-zero if timer is enabled.
    unsigned int value;       // Last value that was set.
    uint64_t expire_time;     // Calculated time that timer will expire.
} opl_timer_t;

typedef int SRWLOCK;

static SRWLOCK callback_mutex;

// Queue of callbacks waiting to be invoked.

static opl_callback_queue_t* callback_queue;

// Mutex used to control access to the callback queue.

static SRWLOCK callback_queue_mutex;

// Current time, in us since startup:

static uint64_t current_time;

// If non-zero, playback is currently paused.

static int opl_stm_paused;

// Time offset (in us) due to the fact that callbacks
// were previously paused.

static uint64_t pause_offset;

// OPL software emulator structure.

#if USE_WOODY_OPL
// todo configure this based on woody build flag
#define opl_op3mode 0
#elif USE_EMU8950_OPL
#define opl_op3mode 0
static OPL* emu8950_opl;
#else
static opl3_chip opl_chip;
static int opl_opl3mode;
#endif

// Register number that was written.

static int register_num = 0;

// Timers; DBOPL does not do timer stuff itself.

static opl_timer_t timer1 = { 12500, 0, 0, 0 };
static opl_timer_t timer2 = { 3125, 0, 0, 0 };


static void OPL_InitMutex(SRWLOCK* lock)
{
    //InitializeSRWLock(lock);
}

static void OPL_LockMutex(SRWLOCK* lock)
{
	HAL_NVIC_DisableIRQ(TIM2_IRQn);
}
static void OPL_UnlockMutex(SRWLOCK* lock)
{
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

// Advance time by the specified number of samples, invoking any
// callback functions as appropriate.

static void AdvanceTime(unsigned int nsamples)
{
    opl_callback_t callback;
    void* callback_data;
    uint64_t us;

    //OPL_LockMutex(&callback_queue_mutex);

    // Advance time.

    us = ((uint64_t)nsamples * OPL_SECOND) / AUDIO_SAMPLE_FREQ;
    current_time += us;

    if (opl_stm_paused)
    {
        pause_offset += us;
    }

    // Are there callbacks to invoke now?  Keep invoking them
    // until there are no more left.

    while (!OPL_Queue_IsEmpty(callback_queue)
        && current_time >= OPL_Queue_Peek(callback_queue) + pause_offset)
    {
        // Pop the callback from the queue to invoke it.

        if (!OPL_Queue_Pop(callback_queue, &callback, &callback_data))
        {
            break;
        }

        // The mutex stuff here is a bit complicated.  We must
        // hold callback_mutex when we invoke the callback (so that
        // the control thread can use OPL_Lock() to prevent callbacks
        // from being invoked), but we must not be holding
        // callback_queue_mutex, as the callback must be able to
        // call OPL_SetCallback to schedule new callbacks.

        //OPL_UnlockMutex(&callback_queue_mutex);

        //OPL_LockMutex(&callback_mutex);
        callback(callback_data);
        //OPL_UnlockMutex(&callback_mutex);

        //OPL_LockMutex(&callback_queue_mutex);
    }

    //OPL_UnlockMutex(&callback_queue_mutex);
}

// Call the OPL emulator code to fill the specified buffer.

static void FillBuffer(uint8_t* buffer, unsigned int nsamples)
{
    // This seems like a reasonable assumption.  mix_buffer is
    // 1 second long, which should always be much longer than the
    // SDL mix buffer.
    assert(nsamples < AUDIO_SAMPLE_FREQ);

    // OPL output is generated into temporary buffer and then mixed
    // (to avoid overflows etc.)
#if USE_WOODY_OPL
    Bit16s* mb16 = (Bit16s*)mix_buffer;
    adlib_getsample(mb16, nsamples);
    for (int i = nsamples - 1; i >= 0; i--) {
        mb16[i * 2] = mb16[i * 2 + 1] = mb16[i];
    }
#elif USE_EMU8950_OPL
#if !EMU8950_NO_RATECONV
    int16_t* buf = (int16_t*)buffer;
    for (int i = 0; i < nsamples; i++) {
        buf[i * 2] = buf[i * 2 + 1] = OPL_calc(emu8950_opl);
    }
#else
    if (nsamples) {
        int32_t* sndptr32 = (int32_t*)(buffer);
        OPL_calc_buffer_stereo(emu8950_opl, sndptr32, nsamples);
    }
#endif
#else
    OPL3_GenerateStream(&opl_chip, (Bit16s*)buffer, nsamples);
    for (int i = 0; i < nsamples * 2; ++i)
    {
        ((Bit16s*)buffer)[i] <<= 3;
    }
#endif
}

// Callback function to fill a new sound buffer:

static void OPL_Mix_Callback(void* udata, uint8_t* buffer, int len)
{
    unsigned int filled, buffer_samples;

    // Repeatedly call the OPL emulator update function until the buffer is
    // full.
    filled = 0;
    buffer_samples = len / 4;

    while (filled < buffer_samples)
    {
        uint64_t next_callback_time;
        uint64_t nsamples;

        //OPL_LockMutex(&callback_queue_mutex);

        // Work out the time until the next callback waiting in
        // the callback queue must be invoked.  We can then fill the
        // buffer with this many samples.

        if (opl_stm_paused || OPL_Queue_IsEmpty(callback_queue))
        {
            nsamples = buffer_samples - filled;
        }
        else
        {
            next_callback_time = OPL_Queue_Peek(callback_queue) + pause_offset;

            nsamples = (next_callback_time - current_time) * AUDIO_SAMPLE_FREQ;
            nsamples = (nsamples + OPL_SECOND - 1) / OPL_SECOND;

            if (nsamples > buffer_samples - filled)
            {
                nsamples = buffer_samples - filled;
            }
        }

        //OPL_UnlockMutex(&callback_queue_mutex);

        // Add emulator output to buffer.

        FillBuffer(buffer + filled * 4, nsamples);
        filled += nsamples;

        // Invoke callbacks for this point in time.

        AdvanceTime(nsamples);
    }
}

static void OPL_STM_Shutdown(void)
{
}

static unsigned int GetSliceSize(void)
{
    int limit;
    int n;

    limit = (opl_sample_rate * MAX_SOUND_SLICE_TIME) / 1000;

    // Try all powers of two, not exceeding the limit.

    for (n = 0;; ++n)
    {
        // 2^n <= limit < 2^n+1 ?

        if ((1 << (n + 1)) > limit)
        {
            return (1 << n);
        }
    }

    // Should never happen?

    return 1024;
}


extern void STM_MixSound(void* buffer, size_t sample_count, size_t byte_size);

void OPL_Music_Generate(void* buffer, unsigned samples)
{
    static int counter = 0;

    OPL_Mix_Callback(NULL, buffer, samples * sizeof(uint16_t) * 2);
    //memset(buffer, 0, samples * sizeof(uint16_t) * 2);
    STM_MixSound(buffer, samples, samples * sizeof(uint16_t) * 2);

    ++counter;
}

void OPL_STM_TimerCallback()
{
    //const unsigned samples = AUDIO_SAMPLE_FREQ * TIMER_FREQ / 1000;
    //OPL_Music_Generate(sample_buf_ptr, samples);

    //sample_buf_ptr += samples * sizeof(uint16_t) * 2;
    //sample_count += samples;
}

extern void AUDIO_Init();

static int OPL_STM_Init(unsigned int port_base)
{
    opl_stm_paused = 0;
    pause_offset = 0;

    // Queue structure of callbacks to invoke.

    callback_queue = OPL_Queue_Create();
    current_time = 0;

    // Create the emulator structure:

#if USE_WOODY_OPL
    adlib_init(mixing_freq);
#elif USE_EMU8950_OPL
    emu8950_opl = OPL_new(3579552, AUDIO_SAMPLE_FREQ); // todo check rate
#else
    OPL3_Reset(&opl_chip, AUDIO_SAMPLE_FREQ);
    opl_opl3mode = 0;
#endif

    OPL_InitMutex(&callback_mutex);
    OPL_InitMutex(&callback_queue_mutex);

    AUDIO_Init();

    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    return 1;
}

static unsigned int OPL_STM_PortRead(opl_port_t port)
{
    unsigned int result = 0;

    if (port == OPL_REGISTER_PORT_OPL3)
    {
        return 0xff;
    }

    if (timer1.enabled && current_time > timer1.expire_time)
    {
        result |= 0x80;   // Either have expired
        result |= 0x40;   // Timer 1 has expired
    }

    if (timer2.enabled && current_time > timer2.expire_time)
    {
        result |= 0x80;   // Either have expired
        result |= 0x20;   // Timer 2 has expired
    }

    return result;
}

static void OPLTimer_CalculateEndTime(opl_timer_t* timer)
{
    int tics;

    // If the timer is enabled, calculate the time when the timer
    // will expire.

    if (timer->enabled)
    {
        tics = 0x100 - timer->value;
        timer->expire_time = current_time
            + ((uint64_t)tics * OPL_SECOND) / timer->rate;
    }
}

static void WriteRegister(unsigned int reg_num, unsigned int value)
{
    switch (reg_num)
    {
    case OPL_REG_TIMER1:
        timer1.value = value;
        OPLTimer_CalculateEndTime(&timer1);
        break;

    case OPL_REG_TIMER2:
        timer2.value = value;
        OPLTimer_CalculateEndTime(&timer2);
        break;

    case OPL_REG_TIMER_CTRL:
        if (value & 0x80)
        {
            timer1.enabled = 0;
            timer2.enabled = 0;
        }
        else
        {
            if ((value & 0x40) == 0)
            {
                timer1.enabled = (value & 0x01) != 0;
                OPLTimer_CalculateEndTime(&timer1);
            }

            if ((value & 0x20) == 0)
            {
                timer1.enabled = (value & 0x02) != 0;
                OPLTimer_CalculateEndTime(&timer2);
            }
        }

        break;

    case OPL_REG_NEW:
#if !USE_WOODY_OPL && !USE_EMU8950_OPL
        opl_opl3mode = value & 0x01;
#endif
    default:
#if USE_WOODY_OPL
        adlib_write(reg_num, value);
#elif USE_EMU8950_OPL
        OPL_writeReg(emu8950_opl, reg_num, value);
#else
        OPL3_WriteRegBuffered(&opl_chip, reg_num, value);
#endif
        break;
    }
}

static void OPL_STM_PortWrite(opl_port_t port, unsigned int value)
{
    if (port == OPL_REGISTER_PORT)
    {
        register_num = value;
    }
    else if (port == OPL_REGISTER_PORT_OPL3)
    {
        register_num = value | 0x100;
    }
    else if (port == OPL_DATA_PORT)
    {
        WriteRegister(register_num, value);
    }
}

static void OPL_STM_SetCallback(uint64_t us, opl_callback_t callback,
    void* data)
{
	us += us/4 + us/8 - us/16; // music seems to play too fast, hack

    OPL_LockMutex(&callback_queue_mutex);
    OPL_Queue_Push(callback_queue, callback, data,
        current_time - pause_offset + us);
    OPL_UnlockMutex(&callback_queue_mutex);
}

static void OPL_STM_ClearCallbacks(void)
{
    OPL_LockMutex(&callback_queue_mutex);
    OPL_Queue_Clear(callback_queue);
    OPL_UnlockMutex(&callback_queue_mutex);
}

static void OPL_STM_Lock(void)
{
    OPL_LockMutex(&callback_mutex);
}

static void OPL_STM_Unlock(void)
{
    OPL_UnlockMutex(&callback_mutex);
}

static void OPL_STM_SetPaused(int paused)
{
    opl_stm_paused = paused;
}

static void OPL_STM_AdjustCallbacks(unsigned int old_tempo, unsigned int new_tempo)
{
    OPL_LockMutex(&callback_queue_mutex);
    OPL_Queue_AdjustCallbacks(callback_queue, current_time, old_tempo, new_tempo);
    OPL_UnlockMutex(&callback_queue_mutex);
}

opl_driver_t opl_stm_driver =
{
    "STM32H7",
    OPL_STM_Init,
    OPL_STM_Shutdown,
    OPL_STM_PortRead,
    OPL_STM_PortWrite,
    OPL_STM_SetCallback,
    OPL_STM_ClearCallbacks,
    OPL_STM_Lock,
    OPL_STM_Unlock,
    OPL_STM_SetPaused,
    OPL_STM_AdjustCallbacks,
};

