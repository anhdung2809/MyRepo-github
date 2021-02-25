#ifndef _QUEUE_H_
#define _QUEUE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdbool.h>
#include <stdint.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_DATA_SIZE   150
#define MAX_QUEUE_SIZE  2
/*******************************************************************************
 * STRUCTURE
 ******************************************************************************/
typedef struct
{
    uint8_t data[MAX_DATA_SIZE];
} queue_data_struct_t;

typedef struct
{
    uint8_t getIndex;
    uint8_t putIndex;
    uint8_t size;
    queue_data_struct_t element[MAX_QUEUE_SIZE];
} queue_struct_t;
/*******************************************************************************
 * API
 ******************************************************************************/
 /*!
 * @brief <Initialize queue data structure>
 *
 * @return <no return>.
 */
void queue_init(void);
/*!
 * @brief <Check whether queue is full>
 *
 * @return <true if the queue is full>.
 */
bool queue_isFull(void);
/*!
 * @brief <Check whether a queue is empty>
 *
 * @return <true if the queue is empty>.
 */
bool queue_isEmpty(void);
/*!
 * @brief <Add a new queue>
 *
 * @return <no return>.
 */
void queue_put(void);
/*!
 * @brief <Get an unused queue>
 *
 * @param outBuff [out] <Pointer point to address of the queue>.
 *
 * @return <no return>.
 */
void queue_getUnuseElement(uint8_t **outBuff);
/*!
 * @brief <Get data from a queue>
 *
 * @param outBuff [out] <Pointer point to data of the queue>.
 *
 * @return <no return.
 */
 void queue_getData(uint8_t **outBuff);
/*!
 * @brief <Get a queue in a list of queue>
 *
 * @return <no return>.
 */
 void queue_get(void);
/*!
 * @brief <Get a queue in a list of queue>
 *
 * @return <no return>.
 */
 void queue_flush(void);
#endif
