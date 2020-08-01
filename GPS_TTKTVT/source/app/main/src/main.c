#include "systick.h"
#include "gpio.h"
#include "usart.h"
#include "gps.h"
#include "lcd16x2.h"
#include "delay.h"
#include <stdio.h>
#include "queue.h"
#include <string.h>
#include "dataParser.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
 static void LCD_UpdatePosition(position_t * position)
 {
    char lcd_Line1[16] = { 0u };
    char lcd_Line2[16] = { 0u };

    sprintf(lcd_Line1, "KD%s%c", position->longitude, position->longDir);
    sprintf(lcd_Line2, "VD%s%c", position->latitude, position->latDir);
    
    LCD16X2_Clear();
    LCD16X2_Gotoxy(0,0);
    LCD16X2_Puts((uint8_t *)lcd_Line1);
    printf("\r\n%s", lcd_Line1);
    
    LCD16X2_Gotoxy(0,1);
    LCD16X2_Puts((uint8_t *) lcd_Line2);
    printf("\r\n%s", lcd_Line2);
 }
int main(void)
 {
    uint8_t * dataPtr = NULL;
    parser_gpsDataFrame_t dataParserBuffer = {0};
    realTime_t realTime;
    position_t position;
	SystemInit();
	LCD16X2_Init();
	//Sys_Delay_Init(72);
    queue_init();
    GPS_Init();
    USART1_Init();
	while(1)
    {
        if (!(queue_isEmpty()))
        {
            //__disable_irq();
            queue_getData(&dataPtr);
            //printf("\r\n%s", dataPtr);
            //printf("\r\n%d", strlen((char *)dataPtr));
                if (dataParser_parse(dataPtr, &dataParserBuffer, strlen((char *) dataPtr) - 1) == true)
                {
                    GPS_GetRealTime(&dataParserBuffer, &realTime);
                    if (GPS_GetPosition(&dataParserBuffer, &position) == true )
                    {
                        LCD_UpdatePosition(&position);
                    }
                }
            queue_get();
            //__enable_irq();
        }
    }
}
