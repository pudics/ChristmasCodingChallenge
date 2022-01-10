#include "digitPower.h"


static inline uint32 calcPow(uint32 num, uint32 exponent);
static inline uint32 getNumberOfDigits(uint32 num);

/*
===================================================
This function computes the power of a given number.
O(log(n)) algorithm
===================================================
 */
static inline uint32 calcPow(uint32 num, uint32 exponent)
{
    uint32 result = 1u;

    while (0u != exponent)
    {
        /* if exp is odd, multiply result by num */
        if (0u != (exponent & 1u)) { result *= num; }

        /* divide exp by 2 */
        exponent >>= 1;

        /* multiply num by itself */
        num *= num;
    }

    return result;
}
/*
================================================================================
This function counts the digits in an integer (optimization for 32-bit numbers).
================================================================================
 */
static inline uint32 getNumberOfDigits(uint32 num)
{
    /* uint32 max value is 4,294,967,295, therefore the number of digits are always less than or equal to 10 */
    return ((num < 10u) ? 1u :
           ((num < 100u) ? 2u :
           ((num < 1000u) ? 3u :
           ((num < 10000u) ? 4u :
           ((num < 100000u) ? 5u :
           ((num < 1000000u) ? 6u :
           ((num < 10000000u) ? 7u :
           ((num < 100000000u) ? 8u :
           ((num < 1000000000u) ? 9u :
                                   10u
           )))))))));
}

/**
 * The digitPower function calculates if the original number is a divider
 * of the sum of the power of the digits.
 *
 * E.g.: 46288 --> 4exp3 + 6exp4+ 2exp5 + 8exp6 + 8exp7 = 2360688 = 46288 * 51
 *
 * It can be assumed that both inputs are > 0.
 *
 * @param  uint32 num: its digits shall be the base of the calculation
 * @param  uint32 exp: to smallest exponent to calculate with
 * @return sint32: -1 if inputNum is not a divider of the calculated value, calculated value / inputNum otherwise
 */
sint32 digitPower(uint32 num, uint32 exponent)
{
    uint32 numCopy = num;
    uint32 digit = 0u;
    uint32 result = 0u;
    register uint32 idx = 1u;

    uint32 numOfDigits = getNumberOfDigits(num);

    for (idx = 1u; idx <= numOfDigits; idx++)
    {
        digit = numCopy % 10u;
        numCopy /= 10u;
        result += calcPow(digit, ((exponent + numOfDigits) - idx));
    }

    {
        /* uint32_max_value 0xFFFFFFFF will be converted to sint32 (-1) (MISRA) */
        uint32 retVal = (0u == (result % num)) ? (result / num) : 0xFFFFFFFFu;
        return (sint32)retVal;
    }
}
