#include "differentDigits.h"


#define DIVISOR (10U)                               /* Macro for the divisor value */
#define DIGIT   (digitArray[inputVal % DIVISOR])    /* Macro to select the nth element of the helper array, where n is the next digit of the base number (using modulo operator) */

/**
 * The differentDigits function calculates how many different digits build up the input value.
 *
 * @param  uint32 inputVal: the base number of different digit calculation
 * @return uint8: the number of different digits within inputVal
 */
uint8 differentDigits(uint32 inputVal)
{
    uint32 retVal = 0u;                                                 /* The number of different digits that inputVal has */
    uint8 digitArray[10] = { 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u };  /* Helper array to count the different digits */

    do
    {                                           /* Looping through every digit in the base number one by one */
        retVal += (uint32)(!(boolean)DIGIT);    /* Increment the return counter value in every case when the nth element of the array is zero (meaning that a new, different digit is found) */
        DIGIT++;                                /* Increment the nth element of the array, indicating that the corresponding inputVal digit is processed */
        inputVal /= DIVISOR;                    /* Divide the base number by ten in order to get the next digit, which will be used to index the helper array in the following cycle */
    } while ((boolean)inputVal);                /* The loop is over when we reach the point that every digit of the input base number is processed (the result of the division is zero) */

    return (uint8)retVal;                       /* Return the counted, different digits in inputVal */
}
