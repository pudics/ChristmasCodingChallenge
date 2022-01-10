#include "convertNumeralSystem.h"


#define UINT32_MAXVALUE		0xFFFFFFFFu

/**
 * The inputBinaryNumber shall be interpreted as a binary number (so the largest valid input is 1111111111).
 * The function shall return with the base-targetNumeralSystem converted value of the inputBinaryNumber.
 * The input targetNumeralSystem may be assumed to be in range [3, 10].
 * If inputBinaryNumber contains other digits than 0 and 1, then return value shall be 0xFFFFFFFF.
 *
 * @param  uint32 inputBinaryNumber: the binary input number to be converted
 * @param  uint8 targetNumeralSystem: inputBinaryNumber shall be converted to this numeral system
 * @return uint32: the base-targetNumeralSystem converted value of inputBinaryNumber
 */
uint32 convertNumeralSystem(uint32 inputBinaryNumber, uint8 targetNumeralSystem)
{
	/* Partial decimal, and the final converted results */
	uint32 decimalResult = 0u;
	uint32 convertedResult = 0u;
	/* Temporary variables for power of 2 and 10 */
	uint32 binaryBase = 1u;
	uint32 decimalBase = 1u;
	/* Temporary variables for digits during calculation */
	uint32 binaryDigit = 0u;
	uint32 targetNumSysDigit = 0u;

		/* ******* First step: calculating decimal number from 'binary' input ******* */
		do
		{
			/* The last digit of inputBinaryNumber */
			binaryDigit = inputBinaryNumber % 10u;

			/* Error check for 'not binary' numbers */
			if(1u < binaryDigit)
			{
				/* The converted result is invalid, and no result for decimal number calculation, end loop */
				convertedResult = UINT32_MAXVALUE;
				decimalResult = 0u;
				break;
			}
			/* Truncate input number */
			inputBinaryNumber = inputBinaryNumber / 10u;
			/* Add decimal equivalent of binary value */
			decimalResult += binaryDigit * binaryBase;
			/* 2 got the Power */
			binaryBase *= 2u;
		}
		while(0u < inputBinaryNumber);

		/* *** Second step: calculating the base-targetNumeralSystem converted value *** */
		do
		{
			/* The last digit of decimalResult from previous cycle */
		    targetNumSysDigit = decimalResult % targetNumeralSystem;
		    /* Put digits in it's right place decimally */
		    convertedResult += targetNumSysDigit * decimalBase;
		    /* Truncate our decimal number */
		    decimalResult = decimalResult/targetNumeralSystem;
		    /* 10 got the Power */
		    decimalBase *= 10u;
		}
		while(0u < decimalResult);

	/* Return converted value */
	return convertedResult;
}
