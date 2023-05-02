#include "stm32h747i_discovery_audio.h"

#define AUDIO_BUFFER_SIZE            (2048*1)

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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ALIGN_32BYTES (static AUDIO_BufferTypeDef  buffer_ctl);
static AUDIO_PLAYBACK_StateTypeDef  audio_state;
__IO uint32_t uwVolume = 20;
__IO uint32_t uwPauseEnabledStatus = 0;
uint32_t bytesread;

static uint32_t AudioFreq[9] ={8000 , 11025, 16000, 22050, 32000, 44100, 48000, 96000, 192000};
uint32_t JoyState;
BSP_AUDIO_Init_t* AudioPlayInit;
/* Private function prototypes -----------------------------------------------*/
static void Audio_SetHint(void);
static uint32_t GetData(void *pdata, uint32_t offset, uint8_t *pbuf, uint32_t NbrOfData);
AUDIO_ErrorTypeDef AUDIO_Start(uint32_t *psrc_address, uint32_t file_size);
AUDIO_ErrorTypeDef AUDIO_Stop(void);

uint8_t AUDIO_Init()
{
	  AudioPlayInit->Device = AUDIO_OUT_DEVICE_HEADPHONE;
	  AudioPlayInit->ChannelsNbr = 2;
	  AudioPlayInit->SampleRate = 49716;
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

	OPL_Music_Generate(ptr, samples);
}

uint8_t AUDIO_Process(void)
{
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
