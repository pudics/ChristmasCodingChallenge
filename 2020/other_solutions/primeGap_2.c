#include "primeGap.h"


/**** MACROS *************************************************************************************/

/**** END OF MACROS ******************************************************************************/


/**** TYPE DEFINITIONS ***************************************************************************/

/**** END OF TYPE DEFINITIONS ********************************************************************/


/**** VARIABLES **********************************************************************************/

/**** END OF VARIABLES ***************************************************************************/


/**** LOCAL FUNCTION DECLARATIONS ****************************************************************/

/* function to check whether the given number is prime */
static boolean isPrime(uint32 num);

/**** END OF LOCAL FUNCTION DECLARATIONS *********************************************************/


/**** LOCAL FUNCTION DEFINITIONS *****************************************************************/

static boolean isPrime(uint32 num)
{
    boolean hasDivider = FALSE;

    /* checking dividers only up to sqrt(num) */
    for (uint32 i = 2u; (i * i) <= num; ++i)
    {
        if ((num % i) == 0u)
        {
            hasDivider = TRUE;
            break;
        }
    }

    /* if num has a divider, then it is not a prime */
    return (TRUE == hasDivider) ? FALSE : TRUE;
}

/**** END OF LOCAL FUNCTION DEFINITIONS **********************************************************/


/**** GLOBAL FUNCTION DEFINITIONS ****************************************************************/

/**
 * The primeGap function calculates the first pair of two prime numbers spaced
 * with gap between the limits lowLimit, highLimit if these numbers exist.
 */
void primeGap(uint16 gap, uint32 lowLimit, uint32 highLimit, uint32 result[])
{
    uint32 lastPrime = 0u;

    result[0] = 0u;
    result[1] = 0u;

    /* lowLimit is used as loop counter */
    for (; lowLimit <= highLimit; ++lowLimit)
    {
        if (isPrime(lowLimit))
        {
            if ((lowLimit - lastPrime) == gap)
            {
                result[0] = lastPrime;
                result[1] = lowLimit;
                break;
            } 
            else
            {
                lastPrime = lowLimit;
            }
        }
    }
}

/**** END OF GLOBAL FUNCTION DEFINITIONS *********************************************************/
