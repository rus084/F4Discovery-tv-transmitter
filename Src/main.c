/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "st25_discovery_lcd.h"
#include "math.h"
#include "3d.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define GPIOA_MODER_8_11 (((uint8_t*)(&(GPIOA->MODER)))[2])
#define GPIOA_OSPEEDR_8_11 (((uint8_t*)(&(GPIOA->OSPEEDR)))[2])
#define MCO_CONTROL_REG GPIOA_OSPEEDR_8_11
#define MCO_ON()  (GPIOA_MODER_8_11) = 2
#define MCO_OFF() (GPIOA_MODER_8_11) = 0
#define MCO_POWER_1() (GPIOA_OSPEEDR_8_11) = 0
#define MCO_POWER_2() (GPIOA_OSPEEDR_8_11) = 1
#define MCO_POWER_3() (GPIOA_OSPEEDR_8_11) = 2
#define MCO_POWER_4() (GPIOA_OSPEEDR_8_11) = 3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
DMA_HandleTypeDef hdma_tim1_up;



/* USER CODE BEGIN PV */

//#define HALF_WIDTH
#ifdef HALF_WIDTH
#define DOUBLE_BUFFER
#define WIDTH 210
#define HALF_DIV 2
#else
#define WIDTH 420
#define HALF_DIV 1
#endif

// paste framebuffer in sram1/2
#pragma location=0x20000000
uint8_t frameBuf[312][WIDTH];
#ifdef DOUBLE_BUFFER
#pragma location=0x2000FFF0
uint8_t frameBuf2[312][WIDTH];
#endif

// flag used for vertical syncronisation
volatile int V_flag = 0;

// callback call's when v blank is begin
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  V_flag = 1;
}

// function wait's while v blank is not occur
void wait_Vsync()
{
  V_flag = 0;
  while (V_flag == 0);
  V_flag = 0;
}

// put white pixel at y,x coordinates
void writeFBW(int y,int x)
{
  if (x>(264/HALF_DIV))
    return;
  
  if (y>200)
    return;
  
  int xReal = x+(72/HALF_DIV);
  int yReal = y+ 24+ 38;
  
  int offset = xReal + (yReal * WIDTH);
  uint8_t* data_ptr = &(    ((uint8_t*)frameBuf)[offset] );
  
  *data_ptr = 0;

}

// y,x - coordinates
// code - color, boolean
void writeFB(int y,int x,int code)
{
  if (x>(264/HALF_DIV))
    return;
  
  if (y>200)
    return;
  
  int xReal = x+(72/HALF_DIV);
  int yReal = y+ 24+ 38;
  
  int offset = xReal + (yReal * WIDTH);
  uint8_t* data_ptr = &(    ((uint8_t*)frameBuf)[offset] );
  
  if (code)
    *data_ptr = 0;
  else
    *data_ptr = 2;
}

void init_fb()
{
  for (int i=0;i<24;i++)
    for (int j=0;j<(420/HALF_DIV);j++)
      frameBuf[i][j] = 3;
  
  for (int i=0;i<312;i++)
    for (int j=(360/HALF_DIV);j<(420/HALF_DIV);j++)
      frameBuf[i][j] = 3;
  
#ifdef DOUBLE_BUFFER
    for (int i=0;i<24;i++)
    for (int j=0;j<(420/HALF_DIV);j++)
      frameBuf2[i][j] = 3;
  
  for (int i=0;i<312;i++)
    for (int j=(360/HALF_DIV);j<(420/HALF_DIV);j++)
      frameBuf2[i][j] = 3;
#endif
}

void clear_fb()
{
    for (int i=24;i<312;i++)
    {
      int offset = (i * WIDTH);
      uint32_t* data_ptr = (uint32_t*)(&((uint8_t*)(frameBuf))[offset]);
      uint32_t pattern = 0x02020202;
      
      for (int j=0;j<(375/HALF_DIV);j+=4)
      {
        *(data_ptr++) = pattern;
      }
    }
}

// draw trinagle with center at 160,50 and size 40x40
// argument - angle of rotation
void drawTrinagle(int angle, pPoint points)
{
      points[0].Y = (int)(160.0f + 40.0f * sinf(angle / 100.0f ));
      points[0].X = (int)(50.0f  + 40.0f * cosf(angle / 100.0f ));
      
      points[1].Y = (int)(160.0f + 40.0f * sinf((angle + 209) / 100.0f ));
      points[1].X = (int)(50.0f  + 40.0f * cosf((angle + 209) / 100.0f ));
      
      points[2].Y = (int)(160.0f + 40.0f * sinf((angle + 418) / 100.0f ));
      points[2].X = (int)(50.0f  + 40.0f * cosf((angle + 418) / 100.0f ));
}

int frameCounter = 0;
int demo1ChangeStateCounter = 0;
int demo1DrawState;

void drawHello()
{
    HAL_Delay(10);
    
    if (demo1ChangeStateCounter++ > 20)
    {
      demo1ChangeStateCounter = 0;
      
      switch (demo1DrawState++)
      {
      case 0:
        BSP_LCD_DisplayStringAtLine(2, " Hello    ");
        break;
      case 1:
        BSP_LCD_DisplayStringAtLine(3, " world    ");
        break;
      case 2:
        BSP_LCD_DisplayStringAtLine(2, "          ");
        break;
      default:
        demo1DrawState = 0;
        BSP_LCD_DisplayStringAtLine(3, "          ");
        break;
      }
    }
    
    {
      Point points[3];
      
      drawTrinagle(frameCounter,points);
      BSP_LCD_DrawPolygon(points, 3);
      
      BSP_LCD_SetColors(0x0000, 0xFFFF);
      drawTrinagle(frameCounter+314,points);
      BSP_LCD_DrawPolygon(points, 3);
      
      BSP_LCD_SetColors(0xFFFF,  0x0000);
      frameCounter++;
      frameCounter%=618;
    }
}

// draw spheres, code from https://github.com/cnlohr/channel3
void drawSpheres()
{
    int x = 0;
    int y = 0;
    SetupMatrix();
    tdRotateEA( ProjectionMatrix, -20, 0, 0 );
    tdRotateEA( ModelviewMatrix, frameCounter, 0, 0 );

    for( y = 3; y >= 0; y-- )
    for( x = 0; x < 4; x++ )
    {
            CNFGColor( x+y*4 );
            ModelviewMatrix[11] = 1000 + tdSIN( (x + y)*40 + frameCounter*2 );
            ModelviewMatrix[3] = 600*x-850;
            ModelviewMatrix[7] = 600*y+800 - 850;
            DrawGeoSphere();
    }
    frameCounter++;
}

// function checks if blue button was pressed
int CheckButton()
{
  static GPIO_PinState last_button = 0;
  GPIO_PinState now_button = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
  int result = 0;
  
  if (now_button>last_button)
    result = 1;
  
  last_button = now_button;
  return result;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  

  
  /* USER CODE END 2 */
  init_fb();
  clear_fb();
#ifdef DOUBLE_BUFFER
  HAL_TIM_Base_Start_DMA_DoubleBuffer(&htim1, (uint32_t*)frameBuf2, (uint32_t*)frameBuf2, (uint32_t*)(&(MCO_CONTROL_REG)) ,sizeof(frameBuf));
#else
  HAL_TIM_Base_Start_DMA_DoubleBuffer(&htim1, (uint32_t*)frameBuf, (uint32_t*)(&frameBuf[0][sizeof(frameBuf)/2]), (uint32_t*)(&(MCO_CONTROL_REG)) ,sizeof(frameBuf)/2);
#endif
  //HAL_TIM_Base_Start_DMA(&htim1, (uint32_t*)frameBuf, (uint32_t*)(&(MCO_CONTROL_REG)) ,sizeof(frameBuf));
  
  BSP_LCD_SetColors(0xFFFF,  0x0000);
  BSP_LCD_SetFont(&Font24);

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
  int DrawMode = 0;

  while (1)
  {
    switch (DrawMode)
    {
    case 0:
      if (CheckButton())
      {
        DrawMode = 1;
        InvadersInit();
      }
      else
      {
        drawHello();
        wait_Vsync();
#ifdef DOUBLE_BUFFER
        memcpy(frameBuf2,frameBuf,sizeof(frameBuf));
#endif
      }
      break;
    case 1:
      if (CheckButton())
      {
        clear_fb();
        BSP_LCD_SetFont(&Font24);
        DrawMode = 2;
      }
      else
      {
        InvadersprocessGame();
#ifdef DOUBLE_BUFFER
        memcpy(frameBuf2,frameBuf,sizeof(frameBuf));
#endif
      }
      break;
    case 2:
      if (CheckButton())
      {
        clear_fb();
        BSP_LCD_SetFont(&Font24);
        DrawMode = 0;
      }
      else
      {
        drawSpheres();
        wait_Vsync();
#ifdef DOUBLE_BUFFER
        memcpy(frameBuf2,frameBuf,sizeof(frameBuf));
#endif
        clear_fb();
      }
    }
    


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 309;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_2);
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
#ifdef HALF_WIDTH
  htim1.Init.Period = 23;
#else
  htim1.Init.Period = 11;
#endif
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
