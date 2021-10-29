/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "eth.h"
#include "tim.h"
#include "usart.h"
#include "usb_otg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "PAJ7620/paj7620.h"
#include "DHT11/dht11.h"
#include "WS2812/ws2812.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
MyUARTHandle uart2, uart3;
uint8_t uartBuf2[100], uartBuf3[100];
WS2812_Dev ws2812Dev1, ws2812Dev2;
uint8_t ledBuf[130];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void CameraLED_Set(uint8_t val)
{
  uint8_t i;
  for(i = 0; i < 12; i++)
    ledBuf[i] = val;
  for(i = 2; i < 12; i += 3) // warmer
    ledBuf[i] = val * 0.7;
  WS2812_Write(&ws2812Dev1, TIM_CHANNEL_2, ledBuf, 12);
}

void StripeLED_Set(uint8_t r, uint8_t g, uint8_t b)
{
  // skip first led
  uint8_t i;
  ledBuf[0] = 0;
  ledBuf[1] = 0;
  ledBuf[2] = 0;
  for(i = 3; i < 129; i += 3)
    ledBuf[i] = g;
  for(i = 4; i < 129; i += 3)
    ledBuf[i] = r;
  for(i = 5; i < 129; i += 3)
    ledBuf[i] = b;
  WS2812_Write(&ws2812Dev2, TIM_CHANNEL_1, ledBuf, 129);
}

void StripeLED_Flow(uint8_t r, uint8_t g, uint8_t b)
{
  // skip first led
  uint8_t i, j;
  for(i = 0; i < 129; i++)
    ledBuf[i] = 0;
  for(i = 0; i < 21; i++)
  {
    ledBuf[(22 - i) * 3 + 0] = ledBuf[(22 - i) * 3 + 1] = ledBuf[(22 - i) * 3 + 2] = 0;
    ledBuf[(21 + i) * 3 + 0] = ledBuf[(21 + i) * 3 + 1] = ledBuf[(21 + i) * 3 + 2] = 0;
    ledBuf[(21 - i) * 3 + 0] = ledBuf[(22 + i) * 3 + 0] = g;
    ledBuf[(21 - i) * 3 + 1] = ledBuf[(22 + i) * 3 + 1] = b;
    ledBuf[(21 - i) * 3 + 2] = ledBuf[(22 + i) * 3 + 2] = r;
    WS2812_Write(&ws2812Dev2, TIM_CHANNEL_1, ledBuf, 129);
    Delay_ms(20);
  }
  ledBuf[3] = ledBuf[4] = ledBuf[5] = 0;
  ledBuf[126] = ledBuf[127] = ledBuf[128] = 0;
  WS2812_Write(&ws2812Dev2, TIM_CHANNEL_1, ledBuf, 129);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  uint8_t gesture;
  uint16_t tmp;
  uint8_t str[30];
  uint8_t tempCnt = 0;
  uint8_t pressed = 0;
  uint32_t i, j;
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
  MX_ETH_Init();
  MX_USART3_UART_Init();
  MX_USB_OTG_FS_PCD_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  Delay_Init(300);
  MyUART_SetOStream(USART3);
  MyUART_Init(&uart3, USART3, uartBuf3, 100);
  MyUART_Init(&uart2, USART2, uartBuf2, 100);
  WS2812_Init(&ws2812Dev1, DMA2_Stream5, DMA_REQUEST_TIM4_UP, DMA2_Stream5_IRQn, &htim4);
  WS2812_Init(&ws2812Dev2, DMA2_Stream6, DMA_REQUEST_TIM2_UP, DMA2_Stream6_IRQn, &htim2);
  printf("Init: %d>", PAJ7620_Init(GPIOF, 6, GPIOF, 7));
  Delay_ms(50);
  CameraLED_Set(0);
  Delay_ms(1);
  CameraLED_Set(0);
  StripeLED_Set(0, 0, 0);
  Delay_ms(50);
  CameraLED_Set(0);
  StripeLED_Set(0, 0, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    Delay_ms(100);
    
    // gesture
    gesture = PAJ7620_Gesture4();
    if(gesture != 0)
      printf("%x>", gesture);
    
    // forward
    if(MyUART_ReadUntilWithZero(&uart2, str, '>'))
      printf("%s>", str);
    
    // temperature
    tempCnt++;
    tempCnt %= 20; // 20 * 100 = 2s
    if(tempCnt == 0)
    {
      DHT11_Refresh();
      printf("t,%.1f,%.1f>", DHT11_GetTemp(), DHT11_GetHumid());
    }
    if(!pressed && HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
    {
      Delay_ms(15);
      if(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
      {
        printf("key>");
        pressed = 1;
      }
    }
    else if(pressed && !HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
    {
      Delay_ms(15);
      if(!HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin))
      {
        pressed = 0;
      }
    }
    if(MyUART_ReadUntilWithZero(&uart3, str, '>'))
    {
      if(str[0] == 'c') // camera light
      {
        if(str[1] == '1')
        {
          i = 1;
          for(; i <= 0x30; i++)
          {
            CameraLED_Set(i);
            Delay_ms(10);
          }
          for(; i <= 0x50; i += 2)
          {
            CameraLED_Set(i);
            Delay_ms(10);
          }
        }
        else
        {
          CameraLED_Set(0);
        }
      }
      else if(str[0] == 's') // stripe
      {
        StripeLED_Set(str[1], str[2], str[3]);
      }
      else if(str[0] == 'f') // stripe flow
      {
        StripeLED_Flow(str[1], str[2], str[3]);
      }
    }
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 75;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 10;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void DMA2_Stream5_IRQHandler(void)
{
  WS2812_UpdateBuf();
}
void DMA2_Stream6_IRQHandler(void)
{
  WS2812_UpdateBuf();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
