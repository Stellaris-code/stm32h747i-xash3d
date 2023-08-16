/*
s_backend.c - sound hardware output
Copyright (C) 2009 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "common.h"
#include "platform/platform.h"

#include "sound.h"
#include "voice.h"

#include "stm32h747i_discovery_audio.h"

#define MAX_SAMPLE_COUNT 0x4000
#define AUDIO_BUFFER_SIZE            (1024*2*2)

/* Private typedef -----------------------------------------------------------*/
typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_INIT,
  AUDIO_STATE_PLAYING,
  AUDIO_STATE_PAUSE
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  BUFFER_OFFSET_NONE = 0,
  BUFFER_OFFSET_HALF,
  BUFFER_OFFSET_FULL,
}BUFFER_StateTypeDef;

typedef struct {
  uint8_t buff[AUDIO_BUFFER_SIZE];
  BUFFER_StateTypeDef state;
}AUDIO_BufferTypeDef;

typedef enum {
  AUDIO_ERROR_NONE = 0,
  AUDIO_ERROR_NOTREADY,
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
}AUDIO_ErrorTypeDef;

static
__attribute__((section(".ramd2.sndbuf")))
ALIGN_32BYTES (AUDIO_BufferTypeDef  buffer_ctl);
static
//__attribute__((section(".ramd2.sndbuf")))
ALIGN_32BYTES (uint16_t hl_dma_buf[MAX_SAMPLE_COUNT * 2]);

static AUDIO_PLAYBACK_StateTypeDef  audio_state;
__IO uint32_t uwVolume = 20;
__IO uint32_t uwPauseEnabledStatus = 0;
uint32_t bytesread;

BSP_AUDIO_Init_t* AudioPlayInit;

uint8_t AUDIO_Init()
{
	  AudioPlayInit->Device = AUDIO_OUT_DEVICE_HEADPHONE;
	  AudioPlayInit->ChannelsNbr = 2;
	  AudioPlayInit->SampleRate = SOUND_DMA_SPEED;
	  AudioPlayInit->BitsPerSample = AUDIO_RESOLUTION_16B;
	  AudioPlayInit->Volume = 100;
	  if(BSP_AUDIO_OUT_Init(0, AudioPlayInit) != 0)
	  {
		  assert(0);
	  }

	  buffer_ctl.state = BUFFER_OFFSET_NONE;
	  bytesread = AUDIO_BUFFER_SIZE;
	  memset(buffer_ctl.buff, 0, AUDIO_BUFFER_SIZE);
	  if(bytesread > 0)
	  {
	    BSP_AUDIO_OUT_Play(0,(uint8_t *)&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE);
	    audio_state = AUDIO_STATE_PLAYING;
	    return AUDIO_ERROR_NONE;
	  }

	  return 0;
}

void AUDIO_FillBuffers(void* ptr, unsigned int bytes)
{
	unsigned int samples = bytes / sizeof(uint16_t) / 2;

	int len     = bytes / sizeof(uint16_t);
	int size    = dma.samples;
	int pos     = dma.samplepos;
	int wrapped = pos + len - size;

	if( wrapped < 0 )
	{
		memcpy( ptr, dma.buffer + ( pos * 2 ), len * 2 );
		dma.samplepos += len;
	}
	else
	{
		int remaining = size - pos;
		memcpy( ptr, dma.buffer + ( pos * 2 ), remaining * 2 );
		if( wrapped > 0 )
			memcpy( ptr + ( remaining * 2 ), dma.buffer, wrapped * 2 );
		dma.samplepos = wrapped;
	}
}

uint8_t AUDIO_Process(void)
{
	if (!dma.initialized)
		return 0;

  uint32_t bytesread;
  AUDIO_ErrorTypeDef error_state = AUDIO_ERROR_NONE;

  switch(audio_state)
  {
  case AUDIO_STATE_PLAYING:

    /* 1st half buffer played; so fill it and continue playing from bottom*/
    if(buffer_ctl.state == BUFFER_OFFSET_HALF)
    {
    	AUDIO_FillBuffers(&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE /2);
    	bytesread = AUDIO_BUFFER_SIZE /2;
    	/*
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[0],
                          AUDIO_BUFFER_SIZE /2);
                          */

      if( bytesread >0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
              /* Clean Data Cache to update the content of the SRAM */
      SCB_CleanDCache_by_Addr((uint32_t*)&buffer_ctl.buff[0], AUDIO_BUFFER_SIZE/2);
      }
    }

    /* 2nd half buffer played; so fill it and continue playing from top */
    if(buffer_ctl.state == BUFFER_OFFSET_FULL)
    {
    	AUDIO_FillBuffers(&buffer_ctl.buff[AUDIO_BUFFER_SIZE /2], AUDIO_BUFFER_SIZE /2);
    	bytesread = AUDIO_BUFFER_SIZE /2;
    	/*
      bytesread = GetData((void *)buffer_ctl.SrcAddress,
                          buffer_ctl.fptr,
                          &buffer_ctl.buff[AUDIO_BUFFER_SIZE /2],
                          AUDIO_BUFFER_SIZE /2);
                          */
      if( bytesread > 0)
      {
        buffer_ctl.state = BUFFER_OFFSET_NONE;
      /* Clean Data Cache to update the content of the SRAM */
      SCB_CleanDCache_by_Addr((uint32_t*)&buffer_ctl.buff[AUDIO_BUFFER_SIZE/2], AUDIO_BUFFER_SIZE/2);
      }
    }
    break;

  default:
    error_state = AUDIO_ERROR_NOTREADY;
    break;
  }
  return (uint8_t) error_state;
}

void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance)
{
    if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 2nd part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance)
{
    if(audio_state == AUDIO_STATE_PLAYING)
  {
    /* allows AUDIO_Process() to refill 1st part of the buffer  */
    buffer_ctl.state = BUFFER_OFFSET_HALF;
  }

}

/**
  * @brief  Manages the DMA FIFO error event.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance)
{
	assert(0);
}

/*
==================
SNDDMA_Init

Try to find a sound device to mix for.
Returns false if nothing is found.
==================
*/

qboolean SNDDMA_Init( void )
{
	AUDIO_Init();

	int samplecount;

	dma.format.speed    = SOUND_DMA_SPEED;
	dma.format.channels = 2;
	dma.format.width    = 2;

	// must be multiple of 64
	samplecount = s_samplecount.value;
	if( !samplecount )
		samplecount = MAX_SAMPLE_COUNT;
	if (samplecount > MAX_SAMPLE_COUNT)
		assert(0);

	dma.samples         = samplecount * 2;
	dma.samplepos       = 0;
	dma.buffer          = hl_dma_buf; // 16 bit
	if( !dma.buffer )
		return false;

	// clearing buffers
	memset( dma.buffer, 0, dma.samples * 2 );


	Con_Printf( "Using BSP audio driver: %d Hz\n", dma.format.speed );

	dma.initialized = true;

	return true;
}


/*
==============
SNDDMA_BeginPainting

Makes sure dma.buffer is valid
===============
*/
void SNDDMA_BeginPainting( void )
{
	HAL_NVIC_DisableIRQ(TIM2_IRQn);
//	SDL_LockAudioDevice( sdl_dev );
}

/*
==============
SNDDMA_Submit

Send sound to device if buffer isn't really the dma buffer
Also unlocks the dsound buffer
===============
*/
void SNDDMA_Submit( void )
{
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
//	SDL_UnlockAudioDevice( sdl_dev );
}

/*
==============
SNDDMA_Shutdown

Reset the sound device for exiting
===============
*/
void SNDDMA_Shutdown( void )
{
}


/*
===========
SNDDMA_Activate
Called when the main window gains or loses focus.
The window have been destroyed and recreated
between a deactivate and an activate.
===========
*/
void SNDDMA_Activate( qboolean active )
{
}


/*
===========
VoiceCapture_Init
===========
*/
qboolean VoiceCapture_Init( void )
{
	return false;
}

/*
===========
VoiceCapture_Activate
===========
*/
qboolean VoiceCapture_Activate( qboolean activate )
{
	return true;
}

/*
===========
VoiceCapture_Lock
===========
*/
qboolean VoiceCapture_Lock( qboolean lock )
{
	return true;
}

/*
==========
VoiceCapture_Shutdown
==========
*/
void VoiceCapture_Shutdown( void )
{
}
