#include "digitPower.h"


static uint32 Exponal(uint8 base, uint32 exponent);

/*
 * Calculates @base ^ @exponent.
 *
 * @param  uint8 base: base of the exponent expression. It is assumed that it is a digit, so it is < 10.
 * @param  uint32 exponent: exponent of the expression. It is assumed that it is > 0.
 * @return uint32: the result of the calculation
 */
static uint32 Exponal(uint8 base, uint32 exponent)
{
    uint32 retVal = base;   /* Return value */
    uint8 i;                /* Cycle counter */

    /* In order to spare some run time, the initial value of retVal is @base, so the cycle can start from 1 */
    for (i = 1u; i < exponent; i++)
    {
        retVal *= base;
    }

    return retVal;
}

/**
 * The digitPower function calculates if the sum of the power of the digits is a divider
 * of the original number.
 *
 * E.g.: 46288 --> 4exp3 + 6exp4+ 2exp5 + 8exp6 + 8exp7 = 2360688 = 46288 * 51
 *
 * It can be assumed that both inputs are > 0.
 *
 * @param  uint32 num: its digits shall be the base of the calculation
 * @param  uint32 exp: to smallest exponent to calculate with
 * @return sint32: -1 if the calculated value is not a divider of inputNum, inputNum / calculated value otherwise
 */
sint32 digitPower(uint32 num, uint32 exp)
{
    uint8 digits[10] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u}; /* Array to store the digits of @num. Max number of digits of an uint32 number is 10 */
    uint32 tempNum = num;       /* Temporary number for the calculations */
    uint8 digitNum = 0u;        /* The number of digits of @num */
    sint32 retVal = -1;         /* Return value */
    uint8 i;                    /* Cycle counter */

    /* Split @num into digits and count their number */
    while (tempNum > 0u)
    {
        digits[digitNum] = (uint8)(tempNum % 10u);
        tempNum /= 10u;
        digitNum++;
    }

    /* Calculate the base exponent outside the 'for' cycle to spare some runtime */
    exp += (uint32)digitNum - 1u;

    /* Assemble the new number according to the formula. Digits are stored in reverse order,
     * therefore the calculation is started at the least significant digit.
     * tempNum is already 0 at this point, so no additional initialization is needed */
    for (i = 0u; i < digitNum; i++)
    {
        tempNum += Exponal(digits[i], exp - i);
    }

    /* Check whether the assembled number is divisible by @num.
     *  If yes, than return the result.
     *  If no, than return the initial -1 */
    if (0u == (tempNum % num))
    {
        retVal = (sint32)tempNum / (sint32)num;
    }

    return retVal;
}
