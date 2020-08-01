#ifndef _DATA_PARSER_H_
#define _DATA_PARSER_H_
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    uint8_t utcPos[9];
    uint8_t date[6];
    uint8_t posStatus;
    uint8_t longDir;
    uint8_t latDir;
    uint8_t longitude[13];
    uint8_t latitude[12];
} parser_gpsDataFrame_t;

bool dataParser_parse(uint8_t * dataPtr, parser_gpsDataFrame_t * buffer, uint8_t dataLen);


#endif /* _DATA_PARSER_H_ */
