/*
 * it.c
 *
 *  Created on: Feb 21, 2021
 *      Author: Anh Dung
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "it.h"

extern UART_HandleTypeDef gHUart2;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&gHUart2);
}
