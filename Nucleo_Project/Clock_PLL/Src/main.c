/*
 * main.c
 *
 *  Created on: Feb 21, 2021
 *      Author: Anh Dung
 */
#include <string.h>
#include "main.h"
#include "stm32f4xx_hal_rcc_ex.h"
#include "stm32f4xx_hal_rcc.h"

/* Declare global uart 2 handle variable */
UART_HandleTypeDef gHUart2;
/**
 * @brief Configure the system clock
 *
 * @return none.
 */
void SystemCoreClockConfig(void);

/**
 * @brief Initialize UART2
 *
 * @return none.
 */
void UART2_Init(void);

/**
 * @brief Error handler
 *
 * @return none.
 */
void Error_Handler(void);

/**
 * @brief Initialize Clock source
 *
 * @param[in] clkSrc The clock source that user want to select
 * @param[in] clkFreq The frequency that user want to set
 * @return none.
 */
void SystemClock_Init(ClockSource_t clkSrc, ClockFreq_t clkFreq);

/**
 * @brief main function
 *
 * @return 0
 */
int main ()
{
	HAL_Init();
	SystemCoreClockConfig();
	SystemClock_Init(clockSource_HSE, clockFreq_180_MHz);
	char msg[100u] = {0u};
	char * data_start = "The application is running\r\n";


	/* Initialize uart 2 */
	UART2_Init();
	/* Transmit data start to uart */
	if (HAL_OK != HAL_UART_Transmit(&gHUart2, (uint8_t*)data_start, (uint16_t)strlen(data_start), HAL_MAX_DELAY))
	{
		Error_Handler();
	}

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK : %ld\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&gHUart2, (uint8_t *)msg, (uint16_t)strlen(msg), HAL_MAX_DELAY);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "HCLK : %ld\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&gHUart2, (uint8_t *)msg, (uint16_t)strlen(msg), HAL_MAX_DELAY);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK1 : %ld\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&gHUart2, (uint8_t *)msg, (uint16_t)strlen(msg), HAL_MAX_DELAY);
	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PCLK2 : %ld\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&gHUart2, (uint8_t *)msg, (uint16_t)strlen(msg), HAL_MAX_DELAY);
	for(;;)
	{

	}

	return 0;
}

void SystemCoreClockConfig(void)
{
	/* Do nothing */
}

void UART2_Init(void)
{
	gHUart2.Instance = USART2;
	gHUart2.Init.BaudRate = 115200;
	gHUart2.Init.HwFlowCtl= UART_HWCONTROL_NONE;
	gHUart2.Init.Mode = UART_MODE_TX_RX;
	gHUart2.Init.OverSampling = UART_OVERSAMPLING_8;
	gHUart2.Init.Parity = UART_PARITY_NONE;
	gHUart2.Init.StopBits = UART_STOPBITS_1;
	gHUart2.Init.WordLength = UART_WORDLENGTH_8B;
	if (HAL_OK != HAL_UART_Init(&gHUart2))
	{
		Error_Handler();
	}
}

void Error_Handler(void)
{
	while(1);
}

void SystemClock_Init(ClockSource_t clkSrc, ClockFreq_t clkFreq) {
	RCC_OscInitTypeDef  rcc_OscInitStruct;
	RCC_ClkInitTypeDef  rcc_ClkInitStruct;
	uint8_t flash_Latency = 0x00u;
	/* Clear garbage memory */
	memset(&rcc_OscInitStruct, 0u, sizeof(RCC_OscInitTypeDef));
	memset(&rcc_OscInitStruct, 0u, sizeof(RCC_ClkInitTypeDef));

	rcc_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	rcc_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

	if (clockSource_HSE == clkSrc)
	{
		rcc_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
		rcc_OscInitStruct.HSEState = RCC_HSE_BYPASS;
		rcc_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
		rcc_OscInitStruct.PLL.PLLM = 8u;
	}
	else if (clockSource_HSI == clkSrc)
	{
		rcc_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		rcc_OscInitStruct.HSIState = RCC_HSI_ON;
		rcc_OscInitStruct.HSICalibrationValue = 16u; // default factory value
		rcc_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		rcc_OscInitStruct.PLL.PLLM = 16u;
	}


	/* Config PLL state */
	rcc_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

	/* Config PLLM, PLLN, PLLP according to input clock frequency*/
	switch(clkFreq)
	{
		case clockFreq_50_MHz:
		{
			rcc_OscInitStruct.PLL.PLLN = 100u;
			rcc_OscInitStruct.PLL.PLLP = 2u;
			rcc_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
			rcc_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
			rcc_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
			flash_Latency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case clockFreq_84_MHz:
		{
			rcc_OscInitStruct.PLL.PLLN = 168u;
			rcc_OscInitStruct.PLL.PLLP = 2u;
			rcc_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
			rcc_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
			rcc_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
			flash_Latency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case clockFreq_120_MHz:
		{
			rcc_OscInitStruct.PLL.PLLN = 240u;
			rcc_OscInitStruct.PLL.PLLP = 2u;
			rcc_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
			rcc_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
			rcc_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
			flash_Latency = FLASH_ACR_LATENCY_1WS;
			break;
		}
		case clockFreq_180_MHz:
		{
			/* Enable clock for power controller*/
			__HAL_RCC_PWR_CLK_ENABLE();
			/* Set regulator power scale as 1*/
			__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
			/* Turn on over drive mode of the voltage regulator */
			__HAL_PWR_OVERDRIVE_ENABLE();
			rcc_OscInitStruct.PLL.PLLN = 360u;
			rcc_OscInitStruct.PLL.PLLP = 2u;
			rcc_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
			rcc_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
			rcc_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
			flash_Latency = FLASH_ACR_LATENCY_5WS;
			break;
		}
		case clockFreq_Undefined:
		default: break;
	}

	/* Enable source clock*/
	if (HAL_OK != HAL_RCC_OscConfig(&rcc_OscInitStruct))
	{
		Error_Handler();
	}
	/* Config bus clock */
	if (HAL_OK != HAL_RCC_ClockConfig(&rcc_ClkInitStruct, flash_Latency))
	{
		Error_Handler();
	}

	/* Redo systick configuration */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

}
