#include "cycle.h"


/**
 * The cycle function calculates the length of the cycle of the reciprocal of inputVal.
 * It can be assumed that inputVal > 1.
 *
 * @param  uint32 inputVal: the cycle shall be calculated for 1/inputVal.
 * @return sint32: -1 if inputVal is not relative prime with 10 otherwise the length of the cycle.
 */
sint32 cycle(uint32 inputVal)
{
    sint32 retVal = 0;

    /* Check if inputVal is relative prime with 10 */
    if ((0u == (inputVal % 2u)) || (0u == (inputVal % 5u)))
    {
        retVal = -1;
    }
    else
    {
        /* Calculate the length of the cycle */
        uint32 firstModulo = 10u % inputVal;
        uint32 currModulo = firstModulo;
        sint32 cycleLength = 1;

        /* The length of the cycle is always less than the inputVal (denominator) */
        while (1)
        {
            /* Solve equation 10^cycleLength % inputVal = 1 */
            /* In the case of recurrent decimals, the length of the cycle is the smallest k, natural number,
             * where 10^k - 1 can be divided without residue with the input value and the input value is relative prime to ten. */
            if (1u == currModulo)
            {
                retVal = cycleLength;
                break;
            }
            else
            {
                currModulo = (currModulo * firstModulo) % inputVal;
                cycleLength++;
            }
        }
    }

    return retVal;
}
