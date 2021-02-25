/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usart.h"
#include "queue.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint8_t * s_dataPtr = NULL;
static uint8_t s_counter = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/

/**
  * @brief Change output of fput to Serial
  */
PUTCHAR_PROTOTYPE
{
  USART_SendData(USART1, (uint8_t) ch);
  /* Loop until data complete tranmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == 0);

  return ch;
}

void USART_putc(USART_TypeDef* USARTx, char ch)
{
  USART_SendData(USARTx, (uint8_t) ch);
  /* Loop until data complete tranmission */
  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == 0);
}

void USART_puts(USART_TypeDef* USARTx, char* str)
{
  while(*str)
  {
    USART_putc(USARTx, *str);
    str++;
  }
}

void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    /*Configure GPIO pin : PA9 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PA10 */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 Operation mode Configuration */
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStruct);

    /* Enable Rx interrup USART1*/
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART1, USART_FLAG_TC);

    /* Enable USART */
    USART_Cmd(USART1, ENABLE);
    
    /* Interrupt config for USART -----------------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART2_Init()
{
 
    GPIO_InitTypeDef SIM_GPIO_Config;
    USART_InitTypeDef SIM_USART_Config;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    /* USART2 pins config */
    SIM_GPIO_Config.GPIO_Pin   = GPIO_Pin_2;
    SIM_GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;	//	Max Freq. is 50 Mhz.
    SIM_GPIO_Config.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA,&SIM_GPIO_Config);
    SIM_GPIO_Config.GPIO_Pin   = GPIO_Pin_3;
    SIM_GPIO_Config.GPIO_Speed = GPIO_Speed_50MHz;	//	Max Freq. is 50 Mhz.
    SIM_GPIO_Config.GPIO_Mode  = GPIO_Mode_IN_FLOATING;	
    GPIO_Init(GPIOA,&SIM_GPIO_Config);

    /* USART mode config */
    SIM_USART_Config.USART_BaudRate   = 9600;
    SIM_USART_Config.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
    SIM_USART_Config.USART_Parity     = USART_Parity_No;
    SIM_USART_Config.USART_StopBits   = USART_StopBits_1;
    SIM_USART_Config.USART_WordLength = USART_WordLength_8b;
    SIM_USART_Config.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &SIM_USART_Config);
    /* Enable interrup when receive data from USART */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ClearFlag(USART2,USART_FLAG_TC);
    /* Enable USART */
    USART_Cmd(USART2, ENABLE);
  
    /* Config SIM USART Interrupt */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    queue_getUnuseElement(&s_dataPtr);
}

void USART2_DeInit(void)
{
    USART_DeInit(USART2);
}

/**
  * @brief  USART2 Interrupt service
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
{
    uint8_t temp;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
        temp = USART_ReceiveData(USART2);
        //printf("%c", temp);
        if (temp == '\n')
        {
            queue_put();
            queue_getUnuseElement(&s_dataPtr);
            s_counter = 0;
        }
        else
        {
            s_dataPtr[s_counter] = temp;
            s_counter++;
        }
    }
}

/************************* End of File ****************************************/
