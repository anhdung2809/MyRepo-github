#ifndef _USART_H
#define	_USART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
/*******************************************************************************
 * API
 ******************************************************************************/
 
/**
  * @brief Send one character to USARTx
  * @param USARTx USART index (x: [1;2])
  * @param ch character input
  * @retval no return
  */
void USART_putc(USART_TypeDef* USARTx, char ch);

/**
  * @brief Send string to USARTx
  * @param USARTx USART index (x : [1;2])
  * @param str string input
  * @retval no return
  */
void USART_puts(USART_TypeDef* USARTx, char * str);

/*!
 * @brief Initialize USART 1
 *
 * @param none.
 * @param none.
 *
 * @return none.
 */
void USART1_Init(void);

/*!
 * @brief Initialize USART 2
 *
 * @param none.
 * @param none.
 *
 * @return none.
 */
void USART2_Init(void);

/*!
 * @brief DeInitialize USART 2
 *
 * @param none.
 * @param none.
 *
 * @return none.
 */
void USART2_DeInit(void);
/************************* End of File ****************************************/

#endif /* USART_H */
