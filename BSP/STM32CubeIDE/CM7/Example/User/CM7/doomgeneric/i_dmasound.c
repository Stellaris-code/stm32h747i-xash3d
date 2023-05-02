//
// Copyright(C) 1993-1996 Id Software, Inc.
// Copyright(C) 2005-2014 Simon Howard
// Copyright(C) 2008 David Flater
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
//	System interface for sound.
//

#define NUM_SOUND_CHANNELS 8
#define SOUND_SAMPLE_FREQ 49716

#include "config.h"

#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "sounds.h"
#include "z_zone.h"

#include "stm32h747i_discovery_audio.h"

#include <math.h>
#include "deh_str.h"
#include "i_sound.h"
#include "m_misc.h"
#include "w_wad.h"

#include "doomtype.h"

#define ADPCM_BLOCK_SIZE 128
#define ADPCM_SAMPLES_PER_BLOCK_SIZE 249
#define LOW_PASS_FILTER
#define MIX_MAX_VOLUME 128
typedef struct channel_s channel_t;

static volatile enum {
    FS_NONE,
    FS_FADE_OUT,
    FS_FADE_IN,
    FS_SILENT,
} fade_state;
#define FADE_STEP 8 // must be power of 2
uint16_t fade_level;

struct channel_s
{
    uint32_t playing;
    const uint8_t* data;
    const uint8_t* data_end;
    uint32_t offset;
    uint32_t step;
    uint8_t left, right; // 0-255
    uint32_t decompressed_size;
#if SOUND_LOW_PASS
    uint8_t alpha256;
#endif
    int16_t* decompressed;
};

static boolean sound_initialized = false;
static channel_t channels[NUM_SOUND_CHANNELS];

static boolean use_sfx_prefix;

static inline bool is_channel_playing(int channel) {
    return channels[channel].decompressed_size != 0 && channels[channel].playing;
}

static inline void stop_channel(int channel) {
    channels[channel].playing = false;
}

static bool check_and_init_channel(int channel) {
    return sound_initialized && ((unsigned int)channel) < NUM_SOUND_CHANNELS;
}

static void WriteWAV(char* filename, byte* data,
    uint32_t length, int samplerate)
{
    FILE* wav;
    unsigned int i;
    unsigned short s;

    wav = fopen(filename, "wb");

    // Header

    fwrite("RIFF", 1, 4, wav);
    i = (signed int)(36 + samplerate);
    fwrite(&i, 4, 1, wav);
    fwrite("WAVE", 1, 4, wav);

    // Subchunk 1

    fwrite("fmt ", 1, 4, wav);
    i = (signed int)(16);
    fwrite(&i, 4, 1, wav);           // Length
    s = (signed short)(1);
    fwrite(&s, 2, 1, wav);           // Format (PCM)
    s = (signed short)(2);
    fwrite(&s, 2, 1, wav);           // Channels (2=stereo)
    i = (signed int)(samplerate);
    fwrite(&i, 4, 1, wav);           // Sample rate
    i = (signed int)(samplerate * 2 * 2);
    fwrite(&i, 4, 1, wav);           // Byte rate (samplerate * stereo * 16 bit)
    s = (signed short)(2 * 2);
    fwrite(&s, 2, 1, wav);           // Block align (stereo * 16 bit)
    s = (signed short)(16);
    fwrite(&s, 2, 1, wav);           // Bits per sample (16 bit)

    // Data subchunk

    fwrite("data", 1, 4, wav);
    i = (signed int)(length);
    fwrite(&i, 4, 1, wav);           // Data length
    fwrite(data, 1, length, wav);    // Data

    fclose(wav);
}

static boolean ExpandSoundData(channel_t* ch, sfxinfo_t* sfxinfo,
    byte* data,
    int samplerate,
    int length)
{
    uint32_t expanded_length;

    // Calculate the length of the expanded version of the sample.

    expanded_length = (uint32_t)((((uint64_t)length) * SOUND_SAMPLE_FREQ) / samplerate);

    // Double up twice: 8 -> 16 bit and mono -> stereo

    expanded_length *= 4;

    if (ch->decompressed)
        Z_Free(ch->decompressed);
    ch->decompressed = Z_Malloc(expanded_length, PU_STATIC, 0);

    // If we can, use the standard / optimized SDL conversion routines.

    {
        int16_t* expanded = (int16_t*)ch->decompressed;
        int expanded_length;
        int expand_ratio;
        int i;

        // Generic expansion if conversion does not work:
        //
        // SDL's audio conversion only works for rate conversions that are
        // powers of 2; if the two formats are not in a direct power of 2
        // ratio, do this naive conversion instead.

        // number of samples in the converted sound

        expanded_length = ((uint64_t)length * SOUND_SAMPLE_FREQ) / samplerate;
        expand_ratio = (length << 8) / expanded_length;

        for (i = 0; i < expanded_length; ++i)
        {
            int16_t sample;
            int src;

            src = (i * expand_ratio) >> 8;

            sample = data[src] | (data[src] << 8);
            sample -= 32768;

            // expand 8->16 bits, mono->stereo

            expanded[i * 2] = expanded[i * 2 + 1] = sample;
        }

#ifdef LOW_PASS_FILTER
        // Perform a low-pass filter on the upscaled sound to filter
        // out high-frequency noise from the conversion process.

        {
            float rc, dt, alpha;

            // Low-pass filter for cutoff frequency f:
            //
            // For sampling rate r, dt = 1 / r
            // rc = 1 / 2*pi*f
            // alpha = dt / (rc + dt)

            // Filter to the half sample rate of the original sound effect
            // (maximum frequency, by nyquist)

            dt = 1.0f / SOUND_SAMPLE_FREQ;
            rc = 1.0f / (3.14f * samplerate);
            alpha = dt / (rc + dt);

            // Both channels are processed in parallel, hence [i-2]:

            for (i = 2; i < expanded_length * 2; ++i)
            {
                expanded[i] = (int16_t)(alpha * expanded[i]
                    + (1 - alpha) * expanded[i - 2]);
            }
        }
#endif /* #ifdef LOW_PASS_FILTER */
    }

    ch->decompressed_size = expanded_length;
    //memset(ch->decompressed, 0, ch->decompressed_size);

    /*
    char filename[128];
    M_snprintf(filename, sizeof(filename), "C:/Users/Ya2nb/Downloads/doomgeneric-master/doomgeneric-master/%s.wav", sfxinfo->name);

    WriteWAV(filename, (uint8_t*)ch->decompressed, expanded_length, SOUND_SAMPLE_FREQ);
    */

    return true;
}

static boolean init_channel_for_sfx(channel_t* ch, const sfxinfo_t* sfxinfo, int pitch)
{
    int lumpnum = sfx_mut(sfxinfo)->lumpnum;
    int lumplen = W_LumpLength(lumpnum);
    int samplerate;
    unsigned int length;

    uint8_t* data = W_CacheLumpNum(lumpnum, PU_STATIC);
    lumplen = W_LumpLength(lumpnum);

    // Check the header, and ensure this is a valid sound

    if (lumplen < 8
        || data[0] != 0x03 || data[1] != 0x00)
    {
        // Invalid sound

        return false;
    }

    // 16 bit sample rate field, 32 bit length field

    samplerate = (data[3] << 8) | data[2];
    length = (data[7] << 24) | (data[6] << 16) | (data[5] << 8) | data[4];

    // If the header specifies that the length of the sound is greater than
    // the length of the lump itself, this is an invalid sound lump

    // We also discard sound lumps that are less than 49 samples long,
    // as this is how DMX behaves - although the actual cut-off length
    // seems to vary slightly depending on the sample rate.  This needs
    // further investigation to better understand the correct
    // behavior.

    if (length > lumplen - 8 || length <= 48)
    {
        return false;
    }

    // The DMX sound library seems to skip the first 16 and last 16
    // bytes of the lump - reason unknown.

    data += 16;
    length -= 32;

    // Sample rate conversion

    if (!ExpandSoundData(ch, sfxinfo, data + 8, samplerate, length))
    {
        return false;
    }


    uint32_t sample_freq = (data[3] << 8) | data[2];
    if (pitch == NORM_PITCH)
        ch->step = sample_freq * 65536 / SOUND_SAMPLE_FREQ;
    else
        ch->step = (uint32_t)((sample_freq * pitch) * 65536ull / (SOUND_SAMPLE_FREQ * pitch));

    ch->offset = 0;
    ch->playing = true;

    return true;
}

static void GetSfxLumpName(const sfxinfo_t* sfx, char* buf, size_t buf_len)
{
    // Linked sfx lumps? Get the lump number for the sound linked to.
    if (sfx->link != NULL)
    {
        sfx = sfx->link;
    }

    // Doom adds a DS* prefix to sound lumps; Heretic and Hexen don't
    // do this.

    if (use_sfx_prefix)
    {
        M_snprintf(buf, buf_len, "ds%s", DEH_String(sfx->name));
    }
    else
    {
        M_StringCopy(buf, DEH_String(sfx->name), buf_len);
    }
}

static void I_STM_PrecacheSounds(should_be_const sfxinfo_t* sounds, int num_sounds)
{
    // no-op
}

static int I_STM_GetSfxLumpNum(should_be_const sfxinfo_t* sfx)
{
    char namebuf[9];
    GetSfxLumpName(sfx, namebuf, sizeof(namebuf));
    return W_GetNumForName(namebuf);
}

static void I_STM_UpdateSoundParams(int handle, int vol, int sep)
{
    int left, right;

    if (!sound_initialized || handle < 0 || handle >= NUM_SOUND_CHANNELS)
    {
        return;
    }

    // todo graham seems unnecessary
    left = ((254 - sep) * vol) / 127;
    right = ((sep)*vol) / 127;

    if (left < 0) left = 0;
    else if (left > 255) left = 255;
    if (right < 0) right = 0;
    else if (right > 255) right = 255;

    channels[handle].left = left;
    channels[handle].right = right;
}

static int I_STM_StartSound(should_be_const sfxinfo_t* sfxinfo, int channel, int vol, int sep, int pitch)
{
    if (!check_and_init_channel(channel)) return -1;

    stop_channel(channel);
    channel_t* ch = &channels[channel];
    if (!init_channel_for_sfx(ch, sfxinfo, pitch)) {
        assert(!is_channel_playing(channel)); // don't expect to have to mark it sotpped
    }
    I_STM_UpdateSoundParams(channel, vol, sep);
    return channel;
}

static void I_STM_StopSound(int channel)
{
    if (check_and_init_channel(channel)) {

    }
}

static boolean I_STM_SoundIsPlaying(int channel)
{
    if (!check_and_init_channel(channel)) return false;
    return is_channel_playing(channel);
}

void STM_MixSound(void* buffer, size_t sample_count, size_t byte_size)
{
    if (!sound_initialized) return;
    if (!buffer) return;

    for (int ch = 0; ch < NUM_SOUND_CHANNELS; ch++) {
        if (is_channel_playing(ch)) {
            channel_t* channel = &channels[ch];
            assert(channel->decompressed_size);
            int voll = channel->left ;
            int volr = channel->right ;
            unsigned int offset_end = channel->decompressed_size * 65536;
            assert(channel->offset < offset_end);
            int16_t* samples = (int16_t*)buffer;
#if SOUND_LOW_PASS
            int alpha256 = channel->alpha256;
            int beta256 = 256 - alpha256;
            int sample = channel->decompressed[channel->offset >> 16];
#endif
            for (int s = 0; s < sample_count; s++) {
#if 0
#if !SOUND_LOW_PASS
                int16_t sample = channel->decompressed[channel->offset >> 16];
                assert((channel->offset >> 16) < channel->decompressed_size);
                //printf("outputting %d\n", sample);
#else
                // todo graham, note that since we are all at the same frequency (and it isn't the end
                //  of the world anyway, we could do this across all channels at once)
                sample = (beta256 * sample + alpha256 * channel->decompressed[channel->offset >> 16]) / 256;
#endif
                * samples++ = sample * voll;
                *samples++ = sample * volr;
                channel->offset += channel->step;
#else
#endif
                int16_t sample = channel->decompressed[channel->offset];
                //sample = (int16_t)(sin(channel->offset / (float)channel->decompressed_size * 8.0 * 4.0 * 100.0) * 32767);
                //printf("sample: %d, %d/%d\n", sample * voll, channel->offset, channel->decompressed_size);
                *samples++ += sample * (voll / 255.0f);
                *samples++ += sample * (volr / 255.0f);

                channel->offset += 2;

                //channel->offset += 1;
                if (channel->offset >= channel->decompressed_size / 2) {
                    stop_channel(ch);
                    assert(!is_channel_playing(ch));
                    channel->offset = 0xdeadbeef;
                    channel->decompressed_size = 0;
                    break;
                }
            }
        }
    }
    if (fade_state == FS_SILENT) {
        memset(buffer, 0, byte_size);
    }
    else if (fade_state != FS_NONE) {
        int16_t* samples = (int16_t*)buffer;
        int fade_step = fade_state == FS_FADE_IN ? FADE_STEP : -FADE_STEP;
        int i;
        for (i = 0; i < sample_count * 2 && fade_level; i += 2) {
            samples[i] = (samples[i] * (int)fade_level) >> 16;
            samples[i + 1] = (samples[i + 1] * (int)fade_level) >> 16;
            fade_level += fade_step;
        }
        if (!fade_level) {
            if (fade_state == FS_FADE_OUT) {
                for (; i < sample_count * 2; i++) {
                    samples[i] = 0;
                }
                fade_state = FS_SILENT;
            }
            else {
                fade_state = FS_NONE;
            }
        }
    }
}

static void I_STM_UpdateSound(void)
{
    if (!sound_initialized) return;
}

static void I_STM_ShutdownSound(void)
{
    if (!sound_initialized)
    {
        return;
    }
    sound_initialized = false;
}

static BSP_AUDIO_Init_t AudioPlayInit;

static boolean I_STM_InitSound(boolean _use_sfx_prefix)
{
    int i;
    use_sfx_prefix = _use_sfx_prefix;

    AudioPlayInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
    AudioPlayInit.ChannelsNbr = 2;
    AudioPlayInit.SampleRate = SOUND_SAMPLE_FREQ;
    AudioPlayInit.BitsPerSample = AUDIO_RESOLUTION_16B;
    AudioPlayInit.Volume = 40;
    if(BSP_AUDIO_OUT_Init(0, &AudioPlayInit) != 0)
    {
    	assert(false);
    }

    sound_initialized = true;
    return true;
}

static snddevice_t sound_pico_devices[] =
{
    SNDDEVICE_SB,
};

sound_module_t sound_stm_module =
{
    sound_pico_devices,
    arrlen(sound_pico_devices),
    I_STM_InitSound,
    I_STM_ShutdownSound,
    I_STM_GetSfxLumpNum,
    I_STM_UpdateSound,
    I_STM_UpdateSoundParams,
    I_STM_StartSound,
    I_STM_StopSound,
    I_STM_SoundIsPlaying,
    I_STM_PrecacheSounds,
};

