#ifndef _GPS_H_
#define _GPS_H_
#include <stdint.h>
#include "dataParser.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
typedef struct
{
    uint8_t hour[3];
    uint8_t minute[3];
    uint8_t second[3];
    uint8_t date[3];
    uint8_t month[3];
    uint8_t year[3];
} realTime_t;

typedef struct
{
    uint8_t longDir;
    uint8_t latDir;
    uint8_t longitude[14];
    uint8_t latitude[13];
} position_t;
/*!
 * @brief Initialize GPS
 *
 * @param none.
 * @param none.
 *
 * @return none.
 */
void GPS_Init(void);

/*!
 * @brief Get real time from GPS data
 *
 * @param none.
 * @param none.
 *
 * @return struct save timing data output.
 */
void GPS_GetRealTime (parser_gpsDataFrame_t * buffer, realTime_t * realTimeBuffer);

/*!
 * @brief Get position from GPS data (longitude and latitude)
 *
 * @param none.
 * @param none.
 *
 * @return struct save position data output.
 */
bool GPS_GetPosition (parser_gpsDataFrame_t * buffer, position_t * posBuffer);

/*!
 * @brief Initialize GPS
 *
 * @param none.
 * @param none.
 *
 * @return none.
 */
void GPS_DeInit(void);

#endif /* _GPS_H_ */
