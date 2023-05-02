#pragma GCC optimize("O3,inline")             // "inline" won't happen without it

#include "doomgeneric/doomkeys.h"

#include "doomgeneric/doomgeneric.h"

#include "stm32_lcd.h"
#include "stm32h7xx_hal.h"
#include "stm32h747i_discovery_lcd.h"
#include "stm32h747i_discovery_ts.h"
#include "stm32h747i_discovery.h"

#include "doomgeneric/i_video.h"
#include "doomgeneric/doomstat.h"

#include <string.h>

#define DISPLAY_WIDTH 800
#define DISPLAY_HEIGHT 480

#define JOYSTATES 8

static unsigned char joystate[JOYSTATES];
static unsigned char lastjoystate[JOYSTATES];

static int mapping[JOYSTATES] =
{
KEY_USE,
KEY_DOWNARROW,
KEY_LEFTARROW,
KEY_RIGHTARROW,
KEY_UPARROW,
KEY_FIRE,
KEY_TAB,
'0'
};

extern DSI_HandleTypeDef  hlcd_dsi;
extern LTDC_HandleTypeDef hlcd_ltdc;
static TS_State_t  TS_State = {0};

static void* buffers[2] =
{
		(void*)LCD_LAYER_0_ADDRESS,
		(void*)LCD_LAYER_0_BUF2_ADDRESS
};
static __IO int32_t  front_buffer   = 0;
static __IO int32_t  pend_buffer   = -1;


#define DISPLAY_FRAME_BUFFER LCD_LAYER_0_ADDRESS

#define DISPLAY_VSYNC 1
#define DISPLAY_VBP 1
#define DISPLAY_VFP 1
#define DISPLAY_VACT DISPLAY_HEIGHT
#define DISPLAY_HSYNC 1
#define DISPLAY_HBP 1
#define DISPLAY_HFP 1
#define DISPLAY_HACT DISPLAY_WIDTH

#define LCD_RESET_PIN                    GPIO_PIN_3
#define LCD_RESET_PULL                   GPIO_NOPULL
#define LCD_RESET_GPIO_PORT              GPIOG
#define LCD_RESET_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOG_CLK_ENABLE()
#define LCD_RESET_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOG_CLK_DISABLE()

static LTDC_HandleTypeDef ltdc = {
	.Instance = LTDC,
	.Init = {
		.HSPolarity = LTDC_HSPOLARITY_AL,
		.VSPolarity = LTDC_VSPOLARITY_AL,
		.DEPolarity = LTDC_DEPOLARITY_AL,
		.PCPolarity = LTDC_PCPOLARITY_IPC,
		.HorizontalSync = DISPLAY_HSYNC,
		.VerticalSync = DISPLAY_VSYNC,
		.AccumulatedHBP = DISPLAY_HSYNC + DISPLAY_HBP,
		.AccumulatedVBP = DISPLAY_VSYNC + DISPLAY_VBP,
		.AccumulatedActiveW = DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_HACT,
		.AccumulatedActiveH = DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_VACT,
		.TotalWidth = DISPLAY_HSYNC + DISPLAY_HBP + DISPLAY_HACT + DISPLAY_HFP,
		.TotalHeigh = DISPLAY_VSYNC + DISPLAY_VBP + DISPLAY_VACT + DISPLAY_VFP,
		.Backcolor = {
			.Blue = 0,
			.Green = 0,
			.Red = 0
		}
	}
};

static DSI_HandleTypeDef dsi = {
	.Instance = DSI,
	.Init = {
		.TXEscapeCkdiv = 0x4,
		.NumberOfLanes = DSI_TWO_DATA_LANES
	}
};

static OTM8009A_Object_t otm8009;

/* LCD clock configuration */
/* PLL3_VCO Input = HSE_VALUE/PLL3M = 5 Mhz */
/* PLL3_VCO Output = PLL3_VCO Input * PLL3N = 800 Mhz */
/* PLLLCDCLK = PLL3_VCO Output/PLL3R = 800/19 = 42 Mhz */
/* LTDC clock frequency = PLLLCDCLK = 42 Mhz */
static RCC_PeriphCLKInitTypeDef lcd_clock_config = {
	.PeriphClockSelection = RCC_PERIPHCLK_LTDC,
	.PLL3 = {
		.PLL3M = 5,
		.PLL3N = 160,
		.PLL3FRACN = 0,
		.PLL3P = 2,
		.PLL3Q = 2,
		.PLL3R = 19
	}
};
static DSI_PLLInitTypeDef dsi_pll_config = {
	.PLLNDIV  = 100,
	.PLLIDF   = DSI_PLL_IN_DIV5,
	.PLLODF  = DSI_PLL_OUT_DIV1
};
static DSI_CmdCfgTypeDef dsi_command_config = {
	.VirtualChannelID = 0,
	.ColorCoding = DSI_RGB888,
	.CommandSize = DISPLAY_HACT,
	.TearingEffectSource = DSI_TE_DSILINK,
	.TearingEffectPolarity = DSI_TE_RISING_EDGE,
	.HSPolarity = DSI_HSYNC_ACTIVE_HIGH,
	.VSPolarity = DSI_VSYNC_ACTIVE_HIGH,
	.DEPolarity = DSI_DATA_ENABLE_ACTIVE_HIGH,
	.VSyncPol = DSI_VSYNC_FALLING,
	.AutomaticRefresh = DSI_AR_DISABLE,
	.TEAcknowledgeRequest = DSI_TE_ACKNOWLEDGE_ENABLE
};
static DSI_PHY_TimerTypeDef dsi_phy_config = {
	.ClockLaneHS2LPTime = 35,
	.ClockLaneLP2HSTime = 35,
	.DataLaneHS2LPTime = 35,
	.DataLaneLP2HSTime = 35,
	.DataLaneMaxReadTime = 0,
	.StopWaitTime = 10
};

static LTDC_LayerCfgTypeDef layer_config = {
	.WindowX0 = 0,
	.WindowX1 = DISPLAY_WIDTH,
	.WindowY0 = 0,
	.WindowY1 = DISPLAY_HEIGHT,
	.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888,
	.Alpha = 255,
	.Alpha0 = 0,
	.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA,
	.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA,
	.FBStartAdress = DISPLAY_FRAME_BUFFER,
	.ImageWidth = DISPLAY_WIDTH,
	.ImageHeight = DISPLAY_HEIGHT,
	.Backcolor = {
		.Blue = 0,
		.Green = 0,
		.Red = 0
	}
};

static DMA2D_HandleTypeDef dma2d = {
	.Instance = DMA2D,
	.Init = {
		.Mode = DMA2D_M2M_PFC,
		.ColorMode = DMA2D_OUTPUT_ARGB8888,
		.OutputOffset = 0,
		.AlphaInverted = DMA2D_REGULAR_ALPHA,  /* No Output Alpha Inversion*/
		.RedBlueSwap = DMA2D_RB_REGULAR     /* No Output Red & Blue swap */
	},
	.LayerCfg = {
		{0},
		{
			.InputOffset = 0,
			.InputColorMode = DMA2D_INPUT_L8,
			.AlphaMode = DMA2D_REPLACE_ALPHA,
			.InputAlpha = 0xFF,
			.AlphaInverted = DMA2D_REGULAR_ALPHA, /* No ForeGround Alpha inversion */
			.RedBlueSwap = DMA2D_RB_REGULAR /* No ForeGround Red/Blue swap */
		}
	}
};

static volatile int refresh_pending = 0;

void bail_if_error(int a, int b, const char* c)
{
	assert(a == b);
}

void HAL_DSI_EndOfRefreshCallback(DSI_HandleTypeDef *hdsi)
{
	refresh_pending = 0;
}

void LCD_MspInit(void)
{
	/** @brief Enable the LTDC clock */
	__HAL_RCC_LTDC_CLK_ENABLE();

	/** @brief Toggle Sw reset of LTDC IP */
	__HAL_RCC_LTDC_FORCE_RESET();
	__HAL_RCC_LTDC_RELEASE_RESET();

	/** @brief Enable the DMA2D clock */
	__HAL_RCC_DMA2D_CLK_ENABLE();

	/** @brief Toggle Sw reset of DMA2D IP */
	__HAL_RCC_DMA2D_FORCE_RESET();
	__HAL_RCC_DMA2D_RELEASE_RESET();

	/** @brief Enable DSI Host and wrapper clocks */
	__HAL_RCC_DSI_CLK_ENABLE();

	/** @brief Soft Reset the DSI Host and wrapper */
	__HAL_RCC_DSI_FORCE_RESET();
	__HAL_RCC_DSI_RELEASE_RESET();

	/** @brief NVIC configuration for LTDC interrupt that is now enabled */
	HAL_NVIC_SetPriority(LTDC_IRQn, 9, 0xf);
	HAL_NVIC_EnableIRQ(LTDC_IRQn);

	/** @brief NVIC configuration for DMA2D interrupt that is now enabled */
	HAL_NVIC_SetPriority(DMA2D_IRQn, 9, 0xf);
	HAL_NVIC_EnableIRQ(DMA2D_IRQn);

	/** @brief NVIC configuration for DSI interrupt that is now enabled */
	HAL_NVIC_SetPriority(DSI_IRQn, 9, 0xf);
	HAL_NVIC_EnableIRQ(DSI_IRQn);
}

void DSI_IRQHandler(void)
{
	HAL_DSI_IRQHandler(&dsi);
}

void DMA2D_IRQHandler(void)
{
	HAL_DMA2D_IRQHandler(&dma2d);
}

static int32_t DSI_IO_Write(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size)
{
	int32_t ret = BSP_ERROR_BUS_FAILURE;
	HAL_StatusTypeDef status;

	if (Size <= 1U) {
		status = HAL_DSI_ShortWrite(&dsi, ChannelNbr, DSI_DCS_SHORT_PKT_WRITE_P1, Reg, (uint32_t)pData[Size]);
		bail_if_error(status, HAL_OK, "HAL_DSI_ShortWrite");
	} else {
		status = HAL_DSI_LongWrite(&dsi, ChannelNbr, DSI_DCS_LONG_PKT_WRITE, Size, (uint32_t)Reg, pData);
		bail_if_error(status, HAL_OK, "HAL_DSI_LongWrite");
	}

	ret = BSP_ERROR_NONE;

bail:
	return ret;
}

static int32_t DSI_IO_Read(uint16_t ChannelNbr, uint16_t Reg, uint8_t *pData, uint16_t Size)
{
	int32_t ret = BSP_ERROR_BUS_FAILURE;
	HAL_StatusTypeDef status;

	status = HAL_DSI_Read(&dsi, ChannelNbr, pData, Size, DSI_DCS_SHORT_PKT_READ, Reg, pData);
	bail_if_error(status, HAL_OK, "HAL_DSI_Read");

	ret = BSP_ERROR_NONE;

bail:
	return ret;
}

int qembd_get_width()
{
	return DISPLAY_WIDTH;
}

int qembd_get_height()
{
	return DISPLAY_HEIGHT;
}

void qembd_vidinit()
{
	GPIO_InitTypeDef gpio_config = {
		.Pin = LCD_RESET_PIN,
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_PULLUP,
		.Speed = GPIO_SPEED_FREQ_VERY_HIGH
	};
	DSI_LPCmdTypeDef dsi_command;
	OTM8009A_IO_t otm8009_io_config = {
		.Address = 0,
		.WriteReg = DSI_IO_Write,
		.ReadReg = DSI_IO_Read,
		.GetTick = HAL_GetTick
	};

	LCD_RESET_GPIO_CLK_ENABLE();
	/* Configure the GPIO Reset pin */
	HAL_GPIO_Init(LCD_RESET_GPIO_PORT , &gpio_config);

	/* Toggle Hardware Reset of the DSI LCD using its XRES signal (active low) */
	/* Activate XRES active low */
	HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT , LCD_RESET_PIN, GPIO_PIN_RESET);
	HAL_Delay(20);/* wait 20 ms */
	HAL_GPIO_WritePin(LCD_RESET_GPIO_PORT , LCD_RESET_PIN, GPIO_PIN_SET);/* Deactivate XRES */
	HAL_Delay(10);/* Wait for 10ms after releasing XRES before sending commands */

	/* Call first MSP Initialize only in case of first initialization
	* This will set IP blocks LTDC, DSI and DMA2D
	* - out of reset
	* - clocked
	* - NVIC IRQ related to IP blocks enabledi
	*/
	//LCD_MspInit();

	/* LCD clock configuration */
	HAL_RCCEx_PeriphCLKConfig(&lcd_clock_config);

	HAL_DSI_DeInit(&dsi);
	HAL_DSI_Init(&dsi, &dsi_pll_config);

	/* Configure the DSI for Command mode */
	HAL_DSI_ConfigAdaptedCommandMode(&dsi, &dsi_command_config);

	dsi_command.LPGenShortWriteNoP    = DSI_LP_GSW0P_ENABLE;
	dsi_command.LPGenShortWriteOneP   = DSI_LP_GSW1P_ENABLE;
	dsi_command.LPGenShortWriteTwoP   = DSI_LP_GSW2P_ENABLE;
	dsi_command.LPGenShortReadNoP     = DSI_LP_GSR0P_ENABLE;
	dsi_command.LPGenShortReadOneP    = DSI_LP_GSR1P_ENABLE;
	dsi_command.LPGenShortReadTwoP    = DSI_LP_GSR2P_ENABLE;
	dsi_command.LPGenLongWrite        = DSI_LP_GLW_ENABLE;
	dsi_command.LPDcsShortWriteNoP    = DSI_LP_DSW0P_ENABLE;
	dsi_command.LPDcsShortWriteOneP   = DSI_LP_DSW1P_ENABLE;
	dsi_command.LPDcsShortReadNoP     = DSI_LP_DSR0P_ENABLE;
	dsi_command.LPDcsLongWrite        = DSI_LP_DLW_ENABLE;
	HAL_DSI_ConfigCommand(&dsi, &dsi_command);

	/* Initialize LTDC */
	HAL_LTDC_DeInit(&ltdc);
	HAL_LTDC_Init(&ltdc);

	/* Start DSI */
	HAL_DSI_Start(&dsi);

	/* Configure DSI PHY HS2LP and LP2HS timings */
	HAL_DSI_ConfigPhyTimer(&dsi, &dsi_phy_config);

	/* Initialize the OTM8009A LCD Display IC Driver (KoD LCD IC Driver) */
	OTM8009A_RegisterBusIO(&otm8009, &otm8009_io_config);
	OTM8009A_Init(&otm8009, OTM8009A_COLMOD_RGB888, OTM8009A_ORIENTATION_LANDSCAPE);

	dsi_command.LPGenShortWriteNoP    = DSI_LP_GSW0P_DISABLE;
	dsi_command.LPGenShortWriteOneP   = DSI_LP_GSW1P_DISABLE;
	dsi_command.LPGenShortWriteTwoP   = DSI_LP_GSW2P_DISABLE;
	dsi_command.LPGenShortReadNoP     = DSI_LP_GSR0P_DISABLE;
	dsi_command.LPGenShortReadOneP    = DSI_LP_GSR1P_DISABLE;
	dsi_command.LPGenShortReadTwoP    = DSI_LP_GSR2P_DISABLE;
	dsi_command.LPGenLongWrite        = DSI_LP_GLW_DISABLE;
	dsi_command.LPDcsShortWriteNoP    = DSI_LP_DSW0P_DISABLE;
	dsi_command.LPDcsShortWriteOneP   = DSI_LP_DSW1P_DISABLE;
	dsi_command.LPDcsShortReadNoP     = DSI_LP_DSR0P_DISABLE;
	dsi_command.LPDcsLongWrite        = DSI_LP_DLW_DISABLE;
	HAL_DSI_ConfigCommand(&dsi, &dsi_command);

	HAL_DSI_ConfigFlowControl(&dsi, DSI_FLOW_CONTROL_BTA);
	HAL_DSI_ForceRXLowPower(&dsi, ENABLE);

	__HAL_DSI_WRAPPER_DISABLE(&dsi);

	/* Layer Init */
	HAL_LTDC_ConfigLayer(&ltdc, &layer_config, 0);

	__HAL_DSI_WRAPPER_ENABLE(&dsi);
}

void qembd_refresh()
{


}

void BlitBmp565(uint32_t x, uint32_t y, void* data, int w, int h)
{
	  /* Configure the DMA2D Mode, Color Mode and output offset */
	  hlcd_dma2d.Init.Mode         = DMA2D_M2M_PFC;
	  hlcd_dma2d.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
	  hlcd_dma2d.Init.OutputOffset = 800 - w;
	  hlcd_dma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */
	  hlcd_dma2d.Init.RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */

	  /* Foreground Configuration */
	  hlcd_dma2d.LayerCfg[1].InputAlpha = 0xFF;
	  hlcd_dma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
	  hlcd_dma2d.LayerCfg[1].InputOffset = 0;
	  hlcd_dma2d.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
	  hlcd_dma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */
	  hlcd_dma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */

	  /* DMA2D Initialization */
	  HAL_DMA2D_Init(&hlcd_dma2d);
	  HAL_DMA2D_ConfigLayer(&hlcd_dma2d, 1);
	  HAL_DMA2D_PollForTransfer(&hlcd_dma2d, 100);

    //while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	  if (HAL_DMA2D_Start(&hlcd_dma2d, (uint32_t)data, (uint32_t)LCD_LAYER_0_ADDRESS + x*4 + y*800*4, w, h) == HAL_OK)
	  {
		/* Polling For DMA transfer */
		  (void)HAL_DMA2D_PollForTransfer(&hlcd_dma2d, 100);
	  }
}

static TS_Init_t hTS;
extern unsigned char bckg[];
extern unsigned char gun[];
extern unsigned char map_active[];
void DG_Init()
{
	DG_ScreenBuffer = (void*)0xD0A00000U;
	memset(joystate, 0, 6);
	memset(lastjoystate, 0, 6);

	qembd_vidinit();

	  uint32_t x_size = DOOMGENERIC_RESX;
	  uint32_t y_size = DOOMGENERIC_RESY;

	  BSP_LCD_GetXSize(0, &x_size);
	  BSP_LCD_GetYSize(0, &y_size);

	  hTS.Width = x_size;
	  hTS.Height = y_size;
	  hTS.Orientation = TS_SWAP_XY | TS_SWAP_Y;
	  hTS.Accuracy = 0;

	  int ret = BSP_TS_Init(0, &hTS);
	  assert(ret == 0);


	  UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
	  memset((void*)LCD_LAYER_0_ADDRESS, 0, x_size * y_size * sizeof(uint32_t));
	  memset((void*)LCD_LAYER_1_ADDRESS, 0, x_size * y_size * sizeof(uint32_t));
	  memset((void*)LCD_LAYER_0_BUF2_ADDRESS, 0, x_size * y_size * sizeof(uint32_t));

	  BlitBmp565(0, 0, (void*)bckg, 800, 480);
	  BlitBmp565(0, y_size-64, (void*)map_active, 64, 64);
	  BlitBmp565(x_size-64, y_size-64, (void*)gun, 64, 64);
	  HAL_DSI_Refresh(&dsi);
}


extern struct color colors[];
extern byte* I_VideoBuffer;

static int dma2d_initialized = 0;

void DG_DrawFrame()
{
	// Wait VSYNC
	while (refresh_pending)
		;

	  // Update input
	  joystate[0] = !HAL_GPIO_ReadPin(JOY1_SEL_GPIO_PORT, JOY1_SEL_PIN);
	  joystate[1] = !HAL_GPIO_ReadPin(JOY1_DOWN_GPIO_PORT, JOY1_DOWN_PIN);
	  joystate[2] = !HAL_GPIO_ReadPin(JOY1_LEFT_GPIO_PORT, JOY1_LEFT_PIN);
	  joystate[3] = !HAL_GPIO_ReadPin(JOY1_RIGHT_GPIO_PORT, JOY1_RIGHT_PIN);
	  joystate[4] = !HAL_GPIO_ReadPin(JOY1_UP_GPIO_PORT, JOY1_UP_PIN);
	  joystate[5] = BSP_PB_GetState(BUTTON_WAKEUP);
	  joystate[6] = 0;
	  joystate[7] = 0;

	  uint32_t ts_status = BSP_TS_GetState(0, &TS_State);
      if(TS_State.TouchDetected)
      {
    	uint32_t x1 = TS_State.TouchX;
    	uint32_t y1 = TS_State.TouchY;

        if (x1 < 64 && y1 > 480-64)
        	joystate[6] = 1;
        else if (x1 > 800-64 && y1 > 480-64)
        	joystate[7] = 1;
      }

	DMA2D_CLUTCfgTypeDef clut_cfg = {
			.pCLUT = colors,
			.CLUTColorMode = DMA2D_CCM_ARGB8888,
			.Size = (256 - 1)	/* The number of CLUT entries is equal to CS[7:0] + 1 */
		};

	  uint32_t x_size = DOOMGENERIC_RESX;
	  uint32_t y_size = DOOMGENERIC_RESY;

	  BSP_LCD_GetXSize(0, &x_size);
	  BSP_LCD_GetYSize(0, &y_size);

	// turn that into DMA!!
	//memcpy((void*)LCD_LAYER_0_ADDRESS, (void*)DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY);

	  uint32_t border_offset = (x_size - DOOMGENERIC_RESX) >> 1;

	  /* Configure the DMA2D Mode, Color Mode and output offset */
	  hlcd_dma2d.Init.Mode         = DMA2D_M2M_PFC;
	  hlcd_dma2d.Init.ColorMode    = DMA2D_OUTPUT_ARGB8888;
	  hlcd_dma2d.Init.OutputOffset = x_size - DOOMGENERIC_RESX;
	  hlcd_dma2d.Init.AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */
	  hlcd_dma2d.Init.RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */


	  /* Foreground Configuration */
	  hlcd_dma2d.LayerCfg[1].InputAlpha = 0xFF;
	  hlcd_dma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_L8;
	  hlcd_dma2d.LayerCfg[1].InputOffset = 0;
	  hlcd_dma2d.LayerCfg[1].AlphaMode = DMA2D_REPLACE_ALPHA;
	  hlcd_dma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA; /* No ForeGround Alpha inversion */
	  hlcd_dma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR; /* No ForeGround Red/Blue swap */

	  uint8_t* out = (uint8_t*)DG_ScreenBuffer;
	  for (unsigned i = 0; i < SCREENHEIGHT; ++i)
	  {
		  for (unsigned k = 0; k < 2; ++k)
			  for (unsigned j = 0; j < SCREENWIDTH; ++j)
			  {
				  *out++   = I_VideoBuffer[i*SCREENWIDTH + j];
				  *out++   = I_VideoBuffer[i*SCREENWIDTH + j];
			  }
	  }

	  SCB_CleanDCache_by_Addr(DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY);

      if (!dma2d_initialized)
      {
		  /* DMA2D Initialization */
		  HAL_DMA2D_Init(&hlcd_dma2d);
		  HAL_DMA2D_ConfigLayer(&hlcd_dma2d, 1);
		  HAL_DMA2D_CLUTLoad(&hlcd_dma2d, clut_cfg, 1);
		  HAL_DMA2D_PollForTransfer(&hlcd_dma2d, 100);
		  dma2d_initialized = 0;
      }

      //while (!(LTDC->CDSR & LTDC_CDSR_VSYNCS));
	  if (HAL_DMA2D_Start(&hlcd_dma2d, (uint32_t)DG_ScreenBuffer, (uint32_t)buffers[0] + border_offset*4, DOOMGENERIC_RESX, DOOMGENERIC_RESY) == HAL_OK)
	  {
		/* Polling For DMA transfer */
		  (void)HAL_DMA2D_PollForTransfer(&hlcd_dma2d, 100);
	  }

		refresh_pending = 1;
		HAL_DSI_Refresh(&dsi);
}

void DG_SleepMs(uint32_t ms)
{
	HAL_Delay(ms);
	//Sleep(ms);
}

uint32_t DG_GetTicksMs()
{
	return HAL_GetTick();
}

static int next_call_ret_enter;
static int next_call_escape;
int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	if (next_call_ret_enter > 0)
	{
		--next_call_ret_enter;
		*doomKey = KEY_ENTER;
		*pressed = next_call_ret_enter >= 0;
		return 1;
	}

	if (next_call_escape > 0)
	{
		--next_call_escape;
		*doomKey = KEY_ESCAPE;
		*pressed = next_call_escape >= 0;
		return 1;
	}

	for (int i = 0; i < JOYSTATES; ++i)
	{
		if (joystate[i] != lastjoystate[i])
		{
			*pressed = joystate[i];
			*doomKey = mapping[i];
			if (*doomKey == KEY_USE && *pressed)
			{
				if (joystate[5]) // KEY_FIRE
					next_call_escape = 1;
				else
					next_call_ret_enter = 1;
			}
			if (i == 7 && *pressed)
			{
				do
				{
					if (mapping[7] == '9')
						mapping[7] = '0';
					else
						++mapping[7];
				} while (!players[consoleplayer].weaponowned[(mapping[7] - '0' + 9) % 10]);
				*doomKey = mapping[i];
			}
			lastjoystate[i] = joystate[i];
			return 1;
		}
	}

	return 0;
}

void DG_SetWindowTitle(const char * title)
{
}
