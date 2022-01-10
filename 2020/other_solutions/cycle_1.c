#include "cycle.h"


static inline uint32 calculateCycleLengthByLongDivison( const uint32 inputVal );
static uint32 isGreatestCommonDenominatorOne ( const uint32 num );
sint32 cycle( uint32 inputVal );

/**
 * When doing long divison we know that we reached the end of the cycle when we reach the same
 * remainder division. e.g.: in the example below we reach the end of cycle when we have to
 * perform the next 100 / 13 division
 *
 *  10 / 13 = 0. -> 10 / 13 = 0.7 -> 10 / 13 = 0.76 -> 10 / 13 = 0.769 ...
 *  100          || 100           || 100            || 100
 *               ||  09           ||  090           ||  090
 *               ||               ||   12           ||   120
 *               ||               ||                ||    03
 *
 * @param  uint32 inputVal: 1st number
 * @return uint32: cycle length
 * */
static inline uint32 calculateCycleLengthByLongDivison( const uint32 inputVal ) {
	uint32 divisionFirstRemainder;
	uint32 divRemainder = 10u * 10u;
	uint32 length = 0u;

	if ( 10u > inputVal){
		divRemainder = (10u % inputVal) * 10u;
	}

	divisionFirstRemainder = divRemainder;

	do {
		divRemainder = ( divRemainder % inputVal ) * 10u;
		length++;
	} while ( divRemainder != divisionFirstRemainder );

	return length;
}

/**
 * Determine if the largest common denominator is greater then one. Since one number is
 * fixed 10 instead of Euclid's Algorithm we check if the number is divisible by 2 or 5
 * to save runtime.
 *
 * @param  uint32 a: 1st number
 * @return uint32: largest common denominator
 * */
static uint32 isGreatestCommonDenominatorOne ( const uint32 num ) {
	uint32 retVal = 0u;

	if ( ( 0u != (num % 5u)) && (0u != (num % 2u)) ) {
		retVal = 1u;
    }

    return retVal;
}

/**
 * The cycle function calculates the length of the cycle of the reciprocal of inputVal.
 * It can be assumed that inputVal > 1.
 *
 * - float32 has effectively only 7-8 decimal digits due to its precision so its not usable
 * - in this 32bit environment modulo factoring works only until 10 to the power of length
 *   is less than UINT32_MAX which is 9, not much better
 * - 10 divided by inputVal is guaranteed to be cyclic if they are relative primes
 * - by doing long divison we find the end of pattern when we preform the exact same remainder
 *   division
 *
 * Due to these considerations we use the traditional division on paper method also known as
 * long division.
 *
 * @param  uint32 inputVal: the cycle shall be calculated for 1/inputVal.
 * @return sint32: -1 if inputVal is relative prime with 10 otherwise the length of the cycle
 */
sint32 cycle( uint32 inputVal ) {
	sint32 exitCode = -1;

	if ( 1u == isGreatestCommonDenominatorOne( inputVal ) ) {
		exitCode = (sint32)calculateCycleLengthByLongDivison( inputVal );
	}

	return exitCode;
}
