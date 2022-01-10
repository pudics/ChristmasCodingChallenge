#include "primeGap.h"


#define MAX_PRIME_GAP    ((uint32)336U) /* Proven that the maximal prime gap under uint32 maxValue (0xFFFFFFFF) is not greater than 336. */

static inline uint8 isPrime(uint32 num);

/*
=======================================================================================================
This function is used for determining whether an input number is prime. Num can only be greater than 2.
- O(sqrt(n)) algorithm

@param[in] num: Containing the number which should be checked.
@return uint8: [FALSE, TRUE]
=======================================================================================================
*/
static inline uint8 isPrime(uint32 num)
{
    uint8 retVal = TRUE;

    if ((3u != num) && ((0u == (num % 2u)) || (0u == (num % 3u)))) /* If a number can be divided by 2 or 3 (except if the number is 3) than it is not a prime. */
    {
        retVal = FALSE;
    }
    else /* If num is divisible by any number between 5 and and sqrt(num), it is not prime. */
    {
        for (register uint32 i = 5u; (i * i) <= num; i += 6u)
        {
            if ((0u == (num % i)) || (0u == (num % (i + 2u))))
            {
                retVal = FALSE;
                break;
            }
        }
    }

    return retVal;
}

/**
 * The primeGap function calculates the first pair of two prime numbers spaced
 * with gap between the limits lowLimit, highLimit if these numbers exist.
 */
void primeGap(uint16 gap, uint32 lowLimit, uint32 highLimit, uint32 result[])
{
    /* Initialize output result array. */
    result[0] = 0u;
    result[1] = 0u;

    /* Check whether inputs are valid. */
    if ((MAX_PRIME_GAP >= gap) && (gap <= (highLimit - lowLimit)))
    {
        const uint32 MAX_LIMIT = highLimit - gap;

        /* Looking for the result (if exists) between lowLimit and highLimit considering the given gap. */
        while (lowLimit <= MAX_LIMIT)
        {
            /* Check whether lowLimit is prime. */
            if (TRUE == isPrime(lowLimit))
            {
                /* Jump forward by 'gap' from lowLimit. */
                uint32 gapJump = lowLimit + gap;

                /* Check whether that number is also prime where we jumped. */
                if (TRUE == isPrime(gapJump))
                {
                    /* Index initialized with 2, because it is sure that a number (except the first prime: 2) followed by a prime is even, which can not be prime. */
                    register uint32 idx = 2u;

                    /* Check if there are any prime numbers between lowLimit and lowLimit + gap.
                     * If a prime is found, then the examined primes are not successive, so the loop is terminated.
                     */
                    while ((idx < gap) && (FALSE == isPrime(lowLimit + idx)))
                    {
                        idx++;
                    }

                    /* Solution is found if first pair of two prime numbers spaced with the given gap between the limits lowLimit, highLimit are exist. */
                    if (idx == gap)
                    {
                        result[0] = lowLimit;
                        result[1] = gapJump;
                        break;
                    }
                    else
                    {
                        /* Skip those numbers for the next iteration which are surely not primes (already calculated above). */
                        lowLimit += idx + 1u;
                    }
                }
                else
                {   /* Skip next number after a prime (always even, except the first prime: 2). */
                    lowLimit += 2;
                }
            }
            else
            {
                lowLimit++;
            }
        }
    }
}
