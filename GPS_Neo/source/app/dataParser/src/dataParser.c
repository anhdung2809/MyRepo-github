#include "dataParser.h"
#include <string.h>

/** @brief define comma position specification */
#define GPS_UTC_POSITION                1
#define GPS_POSITION_STATUS             2
#define GPS_LATITUDE                    3
#define GPS_LATITUDE_DIRECTION          4
#define GPS_LONGITUDE                   5
#define GPS_LONGITUDE_DIRECTION         6
#define GPS_DATE                        9
#define GPS_CHECKSUM                    12

/*!
 * @brief
 * Convert hex to decimal.
 *
 * @param c: hex number input.
 * @param .
 *
 * @return p: decimal number output.
 */
static uint8_t hex_to_decimal(uint8_t c)
{
    uint8_t p;
    if (c >= '0' && c <= '9') {
        p = (uint8_t)(c - '0');
    }
    else if (c >= 'A' && c <= 'F') {
        p = c - 'A' + 10;
    }
    else
        p = 0xFF;
    return p;
}

static uint8_t dataParser_CalculateChecksum(uint8_t * dataPtr, uint8_t dataLen)
{
    uint32_t retVal = 0;
    uint8_t iter = 0;
    
    for(iter = 1; iter < dataLen - 3; iter++)
    {
        retVal ^= dataPtr[iter];
    }
    
    return retVal;
}

static uint32_t dataParser_getChecksum(uint8_t * dataPtr, uint8_t dataLen)
{
    uint8_t retVal = 0;
    
    //printf("%c", dataPtr[dataLen - 2]);
    uint8_t first_byte = hex_to_decimal(dataPtr[dataLen - 2]);
    //printf("%c", dataPtr[dataLen - 1]);
    uint8_t second_byte = hex_to_decimal(dataPtr[dataLen - 1]);
    retVal = first_byte * 16 + second_byte;
    
    return retVal;
}

bool dataParser_parse(uint8_t * dataPtr, parser_gpsDataFrame_t * buffer, uint8_t dataLen)
{
    bool retVal = false;
    uint8_t commaPos = 0;
    uint8_t iter = 0;
    uint8_t jter = 0;
    
//    /** calculate checksum */
    uint8_t temp = dataParser_CalculateChecksum(dataPtr, dataLen);
//    /** get checksum code from data input */
    uint8_t checksum = dataParser_getChecksum(dataPtr, dataLen);
//    
//    /** check checksun */
    if (temp == checksum)
    {
        for (iter = 0; iter < strlen((char *)dataPtr); iter ++)
        {
            if (dataPtr[iter] == ',')
            {
                commaPos += 1;
                jter = 0;
            }
            if (dataPtr[iter + 1] != ',')
            {
                if (commaPos == GPS_UTC_POSITION)
                {
                    buffer->utcPos[jter] = dataPtr[iter + 1];
                    jter++;
                }
                else if (commaPos == GPS_POSITION_STATUS)
                {
                    buffer->posStatus = dataPtr[iter + 1];
                }
                else if (commaPos == GPS_LATITUDE)
                {
                    buffer->latitude[jter] = dataPtr[iter + 1];
                    jter++;
                }
                else if (commaPos == GPS_LATITUDE_DIRECTION)
                {
                    buffer->latDir = dataPtr[iter + 1];
                }
                else if (commaPos == GPS_LONGITUDE)
                {
                    buffer->longitude[jter] = dataPtr[iter + 1];
                    jter++;
                }
                else if (commaPos == GPS_LONGITUDE_DIRECTION)
                {
                    buffer->longDir = dataPtr[iter + 1];
                    jter++;
                }
                else if (commaPos == GPS_DATE)
                {
                    buffer->date[jter] = dataPtr[iter + 1];
                    jter++;
                }
            }            
        }
        retVal = true; 
    }
        
//    for (iter = 0; iter < 80; iter++)
//    {
//      if (dataPtr[iter] == '\0')
//      {
//          break;
//      }
//    }
//    if (iter == 79)
//    {
//        if (dataPtr[3] == 'R' && dataPtr[4] == 'M' && dataPtr[5] == 'C')
//        {
//            /** get utc position */
//            memcpy(buffer->utcPos, (dataPtr + GPS_UTC_POSITION), 9);
//            /** get date */
//            memcpy(buffer->date, (dataPtr + GPS_DATE), 6);
//            /** get position status */
//            buffer->posStatus = dataPtr[GPS_POSITION_STATUS];
//            /** get longitude direction */
//            buffer->longDir = dataPtr[GPS_LONGITUDE_DIRECTION];
//            /** get latitude direction */
//            buffer->latDir = dataPtr[GPS_LATITUDE_DIRECTION];
//            /** get longitude */
//            memcpy(buffer->longitude, (dataPtr + GPS_LONGITUDE), 13);
//            /** get latitude */
//            memcpy(buffer->latitude, (dataPtr + GPS_LATITUDE), 12);
//            retVal = true;
//        }
//    }
    
    return retVal;
}

