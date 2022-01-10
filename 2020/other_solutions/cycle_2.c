#include "cycle.h"


/**
 * The cycle function calculates the length of the cycle of the reciprocal of inputVal.
 * It can be assumed that inputVal > 1.
 *
 * @param  uint32 inputVal: the cycle shall be calculated for 1/inputVal.
 * @return sint32: -1 if inputVal is relative prime with 10 otherwise the length of the cycle
 */
sint32 cycle(uint32 inputVal)
{
    /*
     * Return value is the calculated cycle length.
     * Initial value is -1 which will be returned if inputVal is not relative prime with 10.
     */
    sint32 retVal = -1;

    /* Variable storing the temporary remainder. */
    uint32 remainder = 1U;

    /*
     * Check that inputVal is relative prime with 10:
     * - Check that inputVal is not a multiple of 2
     * - Check that inputVal is not a multiple of 5
     */
    if ((0U != (inputVal & 1U)) && (0U != (inputVal % 5U)))
    {
        /* Start counting cycle length from 0. */
        retVal = 0;

        /* Search until 1 indicates that cycle re-starts. */
        do
        {
            /* Calculate next remainder. */
            remainder = (remainder * 10U) % inputVal;

            /* Increment cycle length. */
            retVal++;
        } while (1U != remainder);
    }

    return retVal;
}
