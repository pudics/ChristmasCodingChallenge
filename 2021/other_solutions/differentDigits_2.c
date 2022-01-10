#include "differentDigits.h"


/**
 * The differentDigits function calculates how many different digits build up the input value.
 *
 * @param  uint32 inputVal: the base number of different digit calculation
 * @return uint8: the number of different digits within inputVal
 */
uint8 differentDigits(uint32 inputVal)
{
	/* Bitfield to store if a digit is used (bit position equals to digit)*/
	uint32 usedDigits = 0u;
	/* Count of unique digits */
	uint32 count = 0u;
	/* Actual digit to process */
	uint32 digit = 0u;

	do
	{
		/* Calculate modulo 10 and shift 1u result times left */
		digit = 1u << (inputVal % 10u); /* parasoft-suppress MISRA2004-12_8 "Result of Modulo 10 will always be less than 10 so shifting 1 to the left by maximum 9 will never exceed the upper limit of uint32, no check needed" */

		/* Check if digit is already used and increase the count of unique digits */
		count += (uint32)(0u == (usedDigits & digit));

		/* Indicate digit usage in the used digits bitfield */
		usedDigits |= digit;

		/* Shrink the input value by a decimal */
		inputVal = inputVal / 10u;
	}
	/* Repeat until the whole number is processed */
	while (0u != inputVal);

	/* Provide the result */
	return (uint8)count;
}
