#include <stdio.h>
#include "gps.h"
#include "usart.h"
#include <string.h>
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

void GPS_Init(void)
{
    /* Initialize USART2 for connecting to GPS module */
    USART2_Init();
}

void GPS_DeInit(void)
{
    USART2_DeInit();
}

void GPS_GetRealTime (parser_gpsDataFrame_t * buffer, realTime_t * realTimeBuffer)
{
    /** Padding null to realTimeBuffer */
    memset(realTimeBuffer->hour, '\0', 18);
    memcpy(realTimeBuffer->hour, buffer->utcPos, 2);
    memcpy(realTimeBuffer->minute, buffer->utcPos + 2, 2);
    memcpy(realTimeBuffer->second, buffer->utcPos + 4, 5);
    memcpy(realTimeBuffer->date, buffer->date, 2);
    memcpy(realTimeBuffer->month, buffer->date + 2, 2);
    memcpy(realTimeBuffer->year, buffer->date + 4, 2);

}

bool GPS_GetPosition (parser_gpsDataFrame_t * buffer, position_t * posBuffer)
{
    bool retVal = false;
    uint8_t positionStatus = buffer->posStatus;
    
    /** Padding null to posBuffer */
    memset(&(posBuffer->longDir), '\0', 30);
    if (positionStatus == 'A')
    {
        memcpy(posBuffer->longitude, buffer->longitude, 13);
        memcpy(posBuffer->latitude, buffer->latitude, 12);
        posBuffer->longDir = buffer->longDir;
        posBuffer->latDir = buffer->latDir;
        retVal = true;
    }
    
    return retVal;
}
