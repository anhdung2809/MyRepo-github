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
 * @return none.
 */
void Clock_Init(void);

/**
 * @brief main function
 *
 * @return 0
 */
int main ()
{
	HAL_Init();
	SystemCoreClockConfig();
	Clock_Init();
	char msg[100u] = {0u};
	char * data_start = "The application is running\r\n";

    /* LETS REDO THE SYSTICK CONFIGURATION */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

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

void Clock_Init(void) {
	RCC_OscInitTypeDef  rcc_OscInitStruct;
	RCC_ClkInitTypeDef  rcc_ClkInitStruct;

	/* Clear garbage memory */
	memset(&rcc_OscInitStruct, 0u, sizeof(RCC_OscInitTypeDef));
	memset(&rcc_OscInitStruct, 0u, sizeof(RCC_ClkInitTypeDef));

	rcc_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	rcc_OscInitStruct.HSEState = RCC_HSE_BYPASS;

	rcc_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	rcc_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
	rcc_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
	rcc_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	rcc_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	/* Enable source clock*/
	if (HAL_OK != HAL_RCC_OscConfig(&rcc_OscInitStruct))
	{
		Error_Handler();
	}
	/* Config bus clock */
	if (HAL_OK != HAL_RCC_ClockConfig(&rcc_ClkInitStruct, FLASH_ACR_LATENCY_0WS))
	{
		Error_Handler();
	}
	__HAL_RCC_HSI_DISABLE(); // disable hsi source clock to save current

}
