/*
 * main.h
 *
 *  Created on: Feb 21, 2021
 *      Author: Anh Dung
 */

#include "stm32f4xx_hal.h"

typedef enum
{
	clockSource_HSI = 0x00u,
	clockSource_HSE = 0x01u,
	clockSoruce_Undefined = 0xFFu,
}ClockSource_t;

typedef enum
{
	clockFreq_50_MHz = 0x00u,
	clockFreq_84_MHz = 0x01u,
	clockFreq_120_MHz = 0x02u,
	clockFreq_180_MHz = 0x03,
	clockFreq_Undefined = 0xFFu,
}ClockFreq_t;
