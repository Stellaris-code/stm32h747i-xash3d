/**
  ******************************************************************************
  * @file    BSP/CM7/Src/main.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the STM32H747I-DISCO BSP Drivers
  *          This is the main program for Cortex-M7.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm_main.h"

#include "stm32h747i_discovery_sd.h"

//#include "doomgeneric/doomgeneric.h"

#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "usbd_cdc_if.h"

/** @addtogroup STM32H7xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

__attribute__((section(".ramd2.m4stack")))
uint8_t cortexm4stack[4096];

uint8_t SetSysClock_PLL_HSI_480(void);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t DemoIndex = 0;
__IO uint8_t NbLoop = 1;

#ifndef USE_FULL_ASSERT
uint32_t    ErrorCounter = 0;
#endif

/* Wave Player Pause/Resume Status. Defined as external in waveplayer.c file */
__IO uint32_t PauseResumeStatus = IDLE_STATUS;

/* Counter for Sel Joystick pressed*/
__IO uint32_t PressCount = 0;
__IO uint32_t ButtonState=0;
uint8_t toggle_led = 0;
__IO uint32_t CameraTest=0;
/* Volume of the audio playback */
/* Initial volume level (from 0% (Mute) to 100% (Max)) */
__IO uint8_t volume = 60;
__IO uint8_t VolumeChange = 0;
__IO uint32_t SRAMTest = 0;
__IO uint32_t SdramTest=0;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Display_DemoDescription(void);
static void MPU_Config(void);
static void CPU_CACHE_Enable(void);
static void HL_demo(void);

extern UART_HandleTypeDef hcom_uart[];

extern void RetargetInit(UART_HandleTypeDef *huart);
extern int start_hl( int argc, char **argv );

BSP_DemoTypedef  BSP_examples[]=
{
  //{Joystick_demo, "JOYSTICK EXTI", 0},
  //{Touchscreen_demo1, "TOUCHSCREEN DEMO1", 0},
  //{Touchscreen_demo2, "TOUCHSCREEN DEMO2", 0},
  //{LCD_demo, "LCD", 0},
  //{Camera_demo, "CAMERA", 0},
  //{AudioPlay_demo, "AUDIO PLAY", 0},
  //{AudioRecord_demo, "AUDIO RECORD", 0},
  //{SD_DMA_demo, "SD", 0},
  //{SD_IT_demo, "SD", 0},
  //{SD_POLLING_demo, "SD", 0},
  //{QSPI_demo, "QSPI", 0},
  //{SDRAM_demo, "SDRAM", 0},
  //{SDRAM_DMA_demo, "SDRAM MDMA", 0},
  {HL_demo, "Half-Life", 0}
};
/* Private functions ---------------------------------------------------------*/

TIM_HandleTypeDef timmy = {0};

/**
  * @brief  Initialize the hardware timer 4.
  * @param  None
  * @retval None
  */
void HardwareTimer4_Init(void)
{
	__TIM2_CLK_ENABLE();	/* Enable TIM4 interface clock */

	/* Desired_timer_frequency = Timer_input_frequency / (prescaler * period)
		 Timer_input_frequency = 84 MHz (same as TIM3, TIM4 is also on APB1)
		 Desired_timer_frequency = 10 Hz (Rotate the LEDs at that frequency for the visuals)
		 ---> prescaler * period = 84 MHz / 100 Hz = 10500000 = 840 * 1000 */

	timmy.Instance = TIM2;																/* Use TIM4 */
	timmy.Init.Prescaler = 1;													/* Set prescaler to 2100 */
	timmy.Init.CounterMode = TIM_COUNTERMODE_DOWN;				/* Count down */
	timmy.Init.Period = 100*1000*1; // 1ms
	timmy.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;		/* Set clock division to 1 */
	timmy.Init.RepetitionCounter = 0;
	timmy.Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;			/* Not using channels */

	/* Initialize the TIM Time Base Unit */
	HAL_TIM_Base_Init(&timmy);

	/* Start TIM3 in interrupt mode */
	HAL_TIM_Base_Start_IT(&timmy);

	/* Set priority for TIM3 IRQ */
	HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);

	/* Enable IRQ for the TIM3 Timer*/
	//HAL_NVIC_EnableIRQ(TIM2_IRQn);
	// Enable the interrupt in the sound init code
}

extern void OPL_STM_TimerCallback(void);

void TIM2_IRQHandler(void)
{
	unsigned ticks_before = HAL_GetTick();

	BSP_LED_Toggle(LED1);
	//AUDIO_Process();
	//OPL_STM_TimerCallback();

	unsigned ticks_after = HAL_GetTick();
	unsigned diff = ticks_after - ticks_before;

	HAL_TIM_IRQHandler(&timmy);
}

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin : CEC_CK_MCO1_Pin */
  GPIO_InitStruct.Pin = CEC_CK_MCO1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(CEC_CK_MCO1_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}


extern void qembd_vidinit();

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

void CortexM4Init()
{
   /* Configure Cortex-M4 Instruction cache through ART accelerator */
   __HAL_RCC_ART_CLK_ENABLE();                   /* Enable the Cortex-M4 ART Clock */
   __HAL_ART_CONFIG_BASE_ADDRESS(0x08000000UL);  /* Configure the Cortex-M4 ART Base address to the Flash Bank 2 : */
   __HAL_ART_ENABLE();                           /* Enable the Cortex-M4 ART */

  /* Set Interrupt Group Priority */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
  BSP_LED_Init(LED1);

	while(1)
	{
		HAL_Delay(1000);
		BSP_LED_Toggle(LED1);
		//__io_putchar('*');
		//__io_putchar('\n');
	}
}

extern uint8_t _sextram, _eextram;
void early_init()
{
	  /* System Init, System clock, voltage scaling and L1-Cache configuration are done by CPU1 (Cortex-M7)
	     in the meantime Domain D2 is put in STOP mode(Cortex-M4 in deep-sleep)
	  */

	  /* Configure the MPU attwributes as Write Through */
	  MPU_Config();

	  /* Enable the CPU Cache */
	 CPU_CACHE_Enable();

	  /* STM32H7xx HAL library initialization:
		   - Systick timer is configured by default as source of time base, but user
			 can eventually implement his proper time base source (a general purpose
			 timer for example or other time source), keeping in mind that Time base
			 duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
			 handled in milliseconds basis.
		   - Set NVIC Group Priority to 4
		   - Low Level Initialization
		 */
	  HAL_Init();


	  /* Configure the system clock to 400 MHz */
	  SystemClock_Config();
	  //int ret = SetSysClock_PLL_HSI_480();
	  //assert(ret == 1);

	  /* SDRAM device configuration */
	  BSP_SDRAM_Init(0);

	  for (uint8_t* p = &_sextram; p != &_eextram; ++p)
	  	*p = 0;
}

int main(void)
{


	// Disable unaligned access faults
  //SCB->CCR = SCB->CCR & ~(1<<3);//Resetting the 3rd bit (meant for enabling hardfault for unaligned access)




  BSP_JOY_Init(JOY1, JOY_MODE_GPIO,JOY_ALL);

  MX_GPIO_Init();
  MX_USB_DEVICE_Init();

  //FMC_Bank1_R->BTCR[0]

  BSP_QSPI_Init_t init ;
  init.InterfaceMode=MT25TL01G_QPI_MODE;
  init.TransferRate= MT25TL01G_DTR_TRANSFER ;
  init.DualFlashMode= MT25TL01G_DUALFLASH_ENABLE;
  BSP_QSPI_Init(0,&init);

  int32_t ret;
  /*
  for (int i = 0; i < 128*1024/64*1024*1024; ++i)
  {
	  ret = BSP_QSPI_EraseBlock(0, i*128*1024, BSP_QSPI_ERASE_128K);
	  assert(ret == BSP_ERROR_NONE);
  }
  */
  ret = BSP_QSPI_EraseChip(0);
  assert(ret == BSP_ERROR_NONE);

  //HAL_Delay(200);

  BSP_QSPI_EnableMemoryMappedMode(0);

  /* When system initialization is finished, Cortex-M7 could wakeup (when needed) the Cortex-M4  by means of
     HSEM notification or by any D2 wakeup source (SEV,EXTI..)   */

  HardwareTimer4_Init();

  /* Configure the Wakeup push-button in EXTI Mode */
  BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_GPIO);
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  /*##-1- Initialize the LCD #################################################*/
  /* Initialize the LCD */
  BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
  BSP_LCD_SetBrightness(0, 100);
//  BSP_LCD_InitEx(0, LCD_ORIENTATION_LANDSCAPE, LCD_PIXEL_FORMAT_RGB888,
//		  800, 400);
  //qembd_vidinit();

  MX_LTDC_LayerConfig_t layerconf;
  layerconf.X0 = layerconf.Y0 = 0;
  layerconf.X1 = 600;
  layerconf.Y1 = 400;
  layerconf.PixelFormat = LCD_PIXEL_FORMAT_RGB565;
  layerconf.Address = 0x24000000; // AXI SRAM

  BSP_LCD_ConfigLayer(0, 0, &layerconf);
  BSP_LCD_SetLayerVisible(0, 0, ENABLE);
  BSP_LCD_SetLayerVisible(0, 1, DISABLE);

  ret = BSP_SD_Init(0);
  if (ret != BSP_ERROR_NONE)
  {
	  printf("--- COULD NOT INITIALIZE THE SD CARD\n");
	  Error_Handler();
  }
  BSP_SD_DetectITConfig(0);

  COM_InitTypeDef COM_Init;

  /* Initialize COM init structure */
  COM_Init.BaudRate   = 115200;
  COM_Init.WordLength = UART_WORDLENGTH_8B;
  COM_Init.StopBits   = COM_STOPBITS_1;
  COM_Init.Parity     = COM_PARITY_NONE;
  COM_Init.HwFlowCtl  = COM_HWCONTROL_NONE;

  BSP_COM_Init(COM1, &COM_Init);
  BSP_COM_SelectLogPort(COM1);

  // no stdout buffering
  setvbuf(stdout, NULL, _IONBF, 0);

  UTIL_LCD_SetFuncDriver(&LCD_Driver);
  UTIL_LCD_SetFont(&UTIL_LCD_DEFAULT_FONT);
  //Display_DemoDescription();
  /* Wait For User inputs */

    HL_demo();

  while (1)
  {
    if(BSP_PB_GetState(BUTTON_WAKEUP) == 1)
    {
      HAL_Delay(400);
      ButtonState = 0;
      BSP_examples[DemoIndex++].DemoFunc();

      HAL_Delay(100);

      if(DemoIndex >= COUNT_OF_EXAMPLE(BSP_examples))
      {
        NbLoop++;
        DemoIndex = 0;
      }
      Display_DemoDescription();
    }
  }

}

volatile unsigned int *DWT_CYCCNT = (int *)0xE0001004;
volatile unsigned int *DWT_CONTROL = (int *)0xE0001000;
volatile unsigned int *SCB_DEMCR = (int *)0xE000EDFC;

static void HL_demo(void)
{
	// Enable cycle counting registers
	*SCB_DEMCR = *SCB_DEMCR | 0x01000000 | (1 << 21) | (1 << 20) | (1 << 17);
	*DWT_CYCCNT = 0; // reset the counter
	*DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter


	// Clear RAM areas
	//memset(0x20000000, 0, 128*1024); // DTCM
	//memset(0x24000000, 0, 512*1024); // RAM_D1
	//memset(0x30000000, 0, 288*1024); // RAM_D2
	//memset(0x38000000, 0, 64*1024);  // RAM_D3

	//UTIL_LCD_Clear(UTIL_LCD_COLOR_BLACK);
	//memset(LCD_LAYER_0_ADDRESS, 0, 800 * 480 * sizeof(uint16_t));
	//memset(LCD_LAYER_1_ADDRESS, 0, 800 * 480 * sizeof(uint32_t));

  // External RAM is initialized, run the static initializers
  __libc_init_array();

	if (vcp_connected())
		vcp_init ();

    char* argv[] = { "xash", "-dev", "5" };
    int argc = sizeof(argv)/sizeof(argv[0]);

    start_hl(argc, argv);
    //doomgeneric_Create(argc, argv);

    for (int i = 0; ; i++)
    {

    	unsigned ticks_before = HAL_GetTick();

        //doomgeneric_Tick();

		//static const char str[] = "The Town Inside Me";
		//CDC_Transmit_HS(str, sizeof(str));

    	unsigned ticks_after = HAL_GetTick();
    	unsigned diff = ticks_after - ticks_before;
    	(void)0;
    }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 400000000 (Cortex-M7 CPU Clock)
  *            HCLK(Hz)                       = 200000000 (Cortex-M4 CPU, Bus matrix Clocks)
  *            AHB Prescaler                  = 2
  *            D1 APB3 Prescaler              = 2 (APB3 Clock  100MHz)
  *            D2 APB1 Prescaler              = 2 (APB1 Clock  100MHz)
  *            D2 APB2 Prescaler              = 2 (APB2 Clock  100MHz)
  *            D3 APB4 Prescaler              = 2 (APB4 Clock  100MHz)
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 5
  *            PLL_N                          = 160
  *            PLL_P                          = 2
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /*!< Supply configuration update enable */
  HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_OFF;
  RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
     Error_Handler();
  }

/* Select PLL as system clock source and configure  bus clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
                                 RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);
  if(ret != HAL_OK)
  {
    Error_Handler();
  }
  //HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
 /*
  Note : The activation of the I/O Compensation Cell is recommended with communication  interfaces
          (GPIO, SPI, FMC, QSPI ...)  when  operating at  high frequencies(please refer to product datasheet)
          The I/O Compensation Cell activation  procedure requires :
        - The activation of the CSI clock
        - The activation of the SYSCFG clock
        - Enabling the I/O Compensation Cell : setting bit[0] of register SYSCFG_CCCSR
 */

  /*activate CSI clock mondatory for I/O Compensation Cell*/
  __HAL_RCC_CSI_ENABLE() ;

  /* Enable SYSCFG clock mondatory for I/O Compensation Cell */
  __HAL_RCC_SYSCFG_CLK_ENABLE() ;

  /* Enables the I/O Compensation Cell */
  HAL_EnableCompensationCell();
}

uint8_t SetSysClock_PLL_HSI_480(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /*!< Supply configuration update enable */
    HAL_PWREx_ConfigSupply(PWR_DIRECT_SMPS_SUPPLY);

    /* Configure the main internal regulator output voltage */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    while (!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

    // Enable HSI oscillator and activate PLL with HSI as source
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_CSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSEState = RCC_HSE_OFF;
    RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;    // 8 MHz
    RCC_OscInitStruct.PLL.PLLN = 120;  // 960 MHz
    RCC_OscInitStruct.PLL.PLLP = 2;    // 480 MHz
    RCC_OscInitStruct.PLL.PLLQ = 8;//96;   // PLL1Q used for FDCAN = 10 MHz
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        return 0; // FAIL
    }

    /* Select PLL as system clock source and configure  bus clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_D1PCLK1 | RCC_CLOCKTYPE_PCLK1 | \
                                   RCC_CLOCKTYPE_PCLK2  | RCC_CLOCKTYPE_D3PCLK1);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        return 0; // FAIL
    }

    //HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
     /*
      Note : The activation of the I/O Compensation Cell is recommended with communication  interfaces
              (GPIO, SPI, FMC, QSPI ...)  when  operating at  high frequencies(please refer to product datasheet)
              The I/O Compensation Cell activation  procedure requires :
            - The activation of the CSI clock
            - The activation of the SYSCFG clock
            - Enabling the I/O Compensation Cell : setting bit[0] of register SYSCFG_CCCSR
     */

      /*activate CSI clock mondatory for I/O Compensation Cell*/
      __HAL_RCC_CSI_ENABLE() ;

      /* Enable SYSCFG clock mondatory for I/O Compensation Cell */
      __HAL_RCC_SYSCFG_CLK_ENABLE() ;

      /* Enables the I/O Compensation Cell */
      HAL_EnableCompensationCell();

    return 1; // OK
}

/**
  * @brief  Display main demo messages
  * @param  None
  * @retval None
  */
static void Display_DemoDescription(void)
{
  char desc[64];
  uint32_t x_size;
  uint32_t y_size;

  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);
  /* Set LCD Foreground Layer  */
  UTIL_LCD_SetFont(&UTIL_LCD_DEFAULT_FONT);

  /* Clear the LCD */
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_Clear(UTIL_LCD_COLOR_WHITE);

  /* Set the LCD Text Color */
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_DARKBLUE);

  /* Display LCD messages */
  UTIL_LCD_DisplayStringAt(0, 10, (uint8_t *)"STM32H747I BSP", CENTER_MODE);
  UTIL_LCD_DisplayStringAt(0, 35, (uint8_t *)"Drivers examples", CENTER_MODE);

  /* Draw Bitmap */
  //UTIL_LCD_DrawBitmap((x_size - 80)/2, 65, (uint8_t *)stlogo);

  UTIL_LCD_SetFont(&Font12);
  UTIL_LCD_DisplayStringAt(0, y_size - 20, (uint8_t *)"Copyright (c) STMicroelectronics 2018", CENTER_MODE);

  UTIL_LCD_SetFont(&Font16);
  BSP_LCD_FillRect(0, 0, y_size/2 + 15, x_size, 60, UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_WHITE);
  UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_BLUE);
  UTIL_LCD_DisplayStringAt(0, y_size / 2 + 30, (uint8_t *)"Press Wakeup button to start :", CENTER_MODE);
  sprintf(desc,"%s example", BSP_examples[DemoIndex].DemoName);
  UTIL_LCD_DisplayStringAt(0, y_size/2 + 45, (uint8_t *)desc, CENTER_MODE);
}

/**
  * @brief  Check for user input
  * @param  None
  * @retval Input state (1 : active / 0 : Inactive)
  */
uint8_t CheckForUserInput(void)
{
  return ButtonState;
}

/**
  * @brief  Button Callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None
  */
void BSP_PB_Callback(Button_TypeDef Button)
{
  if(Button == BUTTON_WAKEUP)
  {

    ButtonState = 1;
  }

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* Turn LED REDon */
  BSP_LED_On(LED_RED);
  while(1)
  {
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/**
  * @brief  Configure the MPU attributes as Write Through for SDRAM.
  * @note   The Base Address is SDRAM_DEVICE_ADDR.
  *         The Region Size is 32MB.
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU as Strongly ordered for not defined regions */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x00;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  // <STM MOD>
  /* Configure the MPU attributes as WB for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = SDRAM_DEVICE_ADDR;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU QSPI flash */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x90000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_128MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*
  // <STM MOD>
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x24000000; // RAM_D1
  MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  */

  // <STM MOD>
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x2000000; // All ram
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  // <STM MOD>
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x0000000; // ITCM
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER4;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  
  // <STM MOD>
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x2000000; // All ram
  MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER5;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}


/**
  * @}
  */

/**
  * @}
  */

