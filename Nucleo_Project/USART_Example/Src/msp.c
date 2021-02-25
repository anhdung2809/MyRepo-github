/*
 * msp.c
 *
 *  Created on: Feb 21, 2021
 *      Author: Anh Dung
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"

void HAL_MspInit(void)
{
	/* Configure low level processor specification */

	/* Set up priority grouping of the arm cortex mx processor */
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* Enable the required system exceptions of the arm cortex mx processor */
	SCB->SHCSR |= 0x07 << 16;

	/* Configure the priority for the system exceptions */
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
	/* Configure low level uart peripheral driver */
	/* Enable clock for uart && GPIOA */
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	/* Pin muxing for uart pin*/
	gpio_uart.Pin = GPIO_PIN_2; // Tx pin
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; // Rx pin
	HAL_GPIO_Init(GPIOA, &gpio_uart);
	/* Enable interrupt for uart */
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	/* Set priority for Rx uart interrupt*/

}
