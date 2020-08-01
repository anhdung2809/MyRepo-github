/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "queue.h"
#include <string.h>
/*******************************************************************************
 * Variables
 ******************************************************************************/
static queue_struct_t s_queueList;
/*******************************************************************************
 * Code
 ******************************************************************************/

void queue_init(void)
{
    s_queueList.getIndex = 0;
    s_queueList.putIndex = 0;
    s_queueList.size = 0;
}

bool queue_isFull(void)
{
    bool retVal = false;
    if (MAX_QUEUE_SIZE == s_queueList.size)
    {
        retVal = true;
    }
    return retVal;
}

bool queue_isEmpty(void)
{
    bool retVal = false;
    if (0 == s_queueList.size)
    {
        retVal = true;
    }
    return retVal;

}

void queue_getUnuseElement(uint8_t ** outBuff)
{
    uint8_t putIndex = s_queueList.putIndex % MAX_QUEUE_SIZE;

    if (!queue_isFull())
    {
        *outBuff = s_queueList.element[putIndex].data;
    }
}

void queue_put(void)
{
    if (!queue_isFull())/* Queue is not full */
    {
        s_queueList.putIndex++;
        s_queueList.size++;
    }
}

void queue_getData(uint8_t ** outBuff)
{
    uint8_t getIndex = s_queueList.getIndex % MAX_QUEUE_SIZE;

    if (!queue_isEmpty())
    {
        *outBuff = s_queueList.element[getIndex].data;
    }
}

void queue_get(void)
{
    uint8_t getIndex = s_queueList.getIndex % MAX_QUEUE_SIZE;
    
    if (!queue_isEmpty())
    {
        /** Clear data buffer before decrease getIndex */
        memset(s_queueList.element[getIndex].data, '\0', sizeof(s_queueList.element[getIndex].data));
        s_queueList.getIndex++;
        s_queueList.size--;
    }
}

