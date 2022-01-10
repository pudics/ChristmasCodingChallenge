#include "bestTravel.h"


#define BIT_SET     ((uint8)1U)
#define BIT_CLEAR   ((uint8)0U)

/**
 * The bestTravel function calculates the best travel for Mary and John.
 *
 * @param  uint32 maxDistance: the maximum distance John wants to travel
 * @param  uint32 numOfTowns: the number of towns Mary wants to visit
 * @param  uint32 distaceList: the list of the distances between the towns
 * @param  uint32 sizeOfDistanceList: the number of distances
 * @return sint32: -1 if there no such travel, and the distance otherwise
 */
sint32 bestTravel(uint32 maxDistance, uint32 numOfTowns, uint32 distaceList[], uint32 sizeOfDistanceList)
{
    uint32 maxSumOfDistances = 0u;            /* Max distance from the summarized distances. */
    uint32 sumOfDistances    = 0u;            /* Summarizing the actual distances. */
    uint32 distanceCntr      = 0u;            /* Counter for the number of processed distances. */
    uint32 counterIdx        = 0u;            /* Index for counter array. */
    uint8 counterArr[sizeOfDistanceList];     /* Array for binary counter approach (only contains 0 or 1). */

    /* Initialize counter array with zeros. */
    for (uint32 i = 0u; i < sizeOfDistanceList; i++)
    {
        counterArr[i] = BIT_CLEAR;
    }

    while (TRUE)
    {
        /* Reset counter index in every cycle. */
        counterIdx = 0u;

        for (uint32 i = 0u; i < sizeOfDistanceList; i++)
        {
            if (BIT_CLEAR != counterArr[i])
            {
                /* Accumulate distances and increment the distance counter to get the actual length of the set. */
                sumOfDistances += distaceList[i];
                distanceCntr++;
            }
        }

        /* Update counter array based on binary counter approach. */
        while ((counterIdx < sizeOfDistanceList) && (BIT_SET == counterArr[counterIdx]))
        {
            counterArr[counterIdx] = BIT_CLEAR;
            counterIdx++;
        }

        /* Select and store maximum of sum of distances. */
        if ((numOfTowns == distanceCntr) && (maxDistance >= sumOfDistances) && (sumOfDistances > maxSumOfDistances))
        {
            maxSumOfDistances = sumOfDistances;
        }

        /* Exit if all subset are processed. */
        if (counterIdx == sizeOfDistanceList)
        {
            break;
        }
        else
        {
            /* Update counter array based on binary counter approach and reset the sum and counter of distances in every cycle. */
            counterArr[counterIdx] = BIT_SET;
            sumOfDistances = 0u;
            distanceCntr = 0u;
        }
    }

    {
        /* uint32_max_value 0xFFFFFFFF will be converted to sint32 (-1) (MISRA). */
        uint32 retVal = (0u == maxSumOfDistances) ? 0xFFFFFFFFu : maxSumOfDistances;
        return (sint32)retVal;
    }
}
