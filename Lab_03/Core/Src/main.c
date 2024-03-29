/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
	
	
	//RED is 6, BLUE is 7, ORANGE is 8, GREEN is 9

//  /*Uses the HAL library to do the LEDS
//__HAL_RCC_GPIOC_CLK_ENABLE(); // Enable the GPIOC clock in the RCC
//	// Set up a configuration struct to pass to the initialization function
//	GPIO_InitTypeDef initStr = {GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, 
//	GPIO_MODE_OUTPUT_PP,
//	GPIO_SPEED_FREQ_LOW,
//	GPIO_NOPULL};
//	HAL_GPIO_Init(GPIOC, &initStr); // Initialize pins PC8 & PC9
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET); // Start PC8 high */

    RCC->AHBENR |=  RCC_AHBENR_GPIOCEN_Msk;

    //GREEN/ORANGE
    GPIOC->MODER |= (1 << 16);
    GPIOC->MODER |= (1 << 18);
    GPIOC->OTYPER &= ~(1 << 8);
    GPIOC->OTYPER &= ~(1 << 9);
    GPIOC->OSPEEDR &= ~(1 << 16); 
    GPIOC->OSPEEDR &= ~(1 << 18);
    GPIOC->PUPDR &= ~(0x00000000); //Set pull down
    GPIOC->ODR &= ~(1 << 8); //Low
    GPIOC->ODR |= (1 << 9); //Green Starts HIGH
	
//		RCC->APB1ENR |= (1<<0) | (1<<1); /* Enable Timer 2 and Timer 3 */
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN; /* Enable Timer 2 and Timer 3 */
		
		//Set peroid for TIM2
		TIM2->PSC = 7999;
		TIM2->ARR = 250;
		
		TIM2->DIER |= (1<<0);
		/*Enable the Timer after applying timer settings */
		TIM2->CR1 |= (1<<0);
		
		//Set Period for TIM3
		//Note that 8MHz is fast enough for getting 800 Hz that we can just set ARR to 10000
		TIM3->ARR = 10000;
		TIM3->DIER |= (1<<0);
	 
		/*PWM Section*/
		TIM3->CCMR1 &= ~(1<<0) | ~(1<<1); // CCS1 Output Mode
		TIM3->CCMR1	&= ~(1<<8) | ~(1<<9); // CCS2 Output Mode
	
		TIM3->CCMR1 |= 0x70; //set output channel 1 to PWM Mode 2
		TIM3->CCMR1 |= (0x7000 & 0xEFFF); //set channel 2 to PWM Mode 1.
		TIM3->CCMR1 |= 0x808; //sets bits 3 and 11 high.  Enable the output compare preload for both channels
		TIM3->CCER |= 0x11; //sets bits 0 and 4 high.  Set the output enable bits for channels 1 & 2
	
		//Setting channel 1 and 2 to 20% of the ARR for TIM3
		TIM3->CCR1 = 2000;
		TIM3->CCR2 = 2000;
		//-----
		TIM3->CR1 |= 1;

	
		//Enable in TIM2 NVIC
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, 1); // Change the priority to 1 to starve Systick, to 3 to allow Systick
	
		//PC6 and PC7 alternate function mode section
			//RED/BLUE
		GPIOC->MODER |= (1 << 13); //Set MODER 6 (bit 16) to alternate function mode
		GPIOC->MODER |= (1 << 15); //Set MODER 7 (bit 18) to alternate function mode
		GPIOC->OTYPER &= ~(1 << 6); //Set to 0 for push pull
		GPIOC->OTYPER &= ~(1 << 7);
		GPIOC->OSPEEDR &= ~(1 << 12); //Set to 0 for low speed
		GPIOC->OSPEEDR &= ~(1 << 14); 
//	GPIOC->ODR &= ~(1 << 7); //Low
//	GPIOC->ODR &= ~(1 << 6); //Low
		GPIOC->AFR[0] |= 0x0 << GPIO_AFRL_AFRL0_Pos; //Set 0000 to select AF0
		
		
	
	/* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void TIM2_IRQHandler(void)
{
	GPIOC->ODR ^= (1<<8);
	GPIOC->ODR ^= (1<<9);
	TIM2->SR &= ~(1<<0); /* Bit 0 UIF: Update interrupt flag --- this clears the flag in the TIM2 Status Register */
	
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
