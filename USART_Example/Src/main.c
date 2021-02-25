/*
 * main.c
 *
 *  Created on: Feb 21, 2021
 *      Author: Anh Dung
 */
#include "main.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

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
 * @biref Convert character to upper case
 *
 * @param[in] char character want to convert to upper case
 *
 * @return none.
 */
uint8_t toUpperCase(uint8_t character);

uint16_t byteCount = 0u;
uint8_t dataBuffer[100] = { 0u };
uint8_t byteInt_Temp = 0u;

/**
 * @brief main function
 *
 * @return 0
 */
int main ()
{
	char * data_start = "The application is running\r";
	HAL_Init();
	SystemCoreClockConfig();
	UART2_Init();

	/* Transmit data start to uart */
	if (HAL_OK != HAL_UART_Transmit(&gHUart2, (uint8_t*)data_start, (uint16_t)strlen(data_start), HAL_MAX_DELAY))
	{
		Error_Handler();
	}
	/* set up for receiving the first byte */
	(void)HAL_UART_Receive_IT(&gHUart2, &byteInt_Temp, 1);
	for(;;)
	{
		/* set up for receiving any next byte */
		(void)HAL_UART_Receive_IT(&gHUart2, &byteInt_Temp, 1);
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

uint8_t toUpperCase(uint8_t character)
{
	uint8_t retVal = character;

	if (character >= 'a' && character <= 'z')
	{
		retVal = character - 32;
	}

	return retVal;
}

void Error_Handler(void)
{
	while(1);
}

/**
 * @brief Handle after receiving data completely
 *
 * */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	dataBuffer[byteCount++] = toUpperCase(byteInt_Temp);
	if ('\r' == byteInt_Temp)
	{
		HAL_UART_Transmit(&gHUart2, dataBuffer, (uint16_t)byteCount, HAL_MAX_DELAY);
		byteCount = 0;
	}
}
