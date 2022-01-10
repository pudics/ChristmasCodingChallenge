#include "bestTravel.h"


static uint32 countSetBits( uint32 num );
static uint32 calculateMaskedSum( const uint32 distaceList[], uint32 mask );

/**
 * Calculate the number of bits set in num
 *
 * @param  uint32 num: number to evaulate
 * @return uint32: number of set bits in num
 */
static uint32 countSetBits( uint32 num ){
	uint32 count = 0u;

	while ( 0u != num ){
		count += num & (uint32)1u;
		num >>= 1u;
	}

	return count;
}

/**
 * Calculate sum of array members indicated by the bit positions in the mask
 *
 * @param  uint32 distaceList: array of numbers
 * @param  uint32 mask: mask where each bit represents the coresponding array position
 * @return uint32: sum of indicated array members
 */
static uint32 calculateMaskedSum( const uint32 distaceList[], uint32 mask ){
	uint32 result = 0u;
	uint32 iter = 0u;

	for ( ; 0u < mask; ){
		if ( 0u != (mask & 1u) ){
			result += distaceList[ iter ];
		}
		mask >>= 1u;
		iter++;
	}

	return result;
}

/**
 * The bestTravel function calculates the est travel for Mary and John.
 *
 * -----
 * Classical recursive task, that is faster if we implement it in a loop in C.
 *
 * BUT no matter what loop or recursive solution we chose, we can not avoid a MISRA violation for
 * dynamic memory allocation in some form, so we have to use another method. The main reason is the
 * need for numOfTowns number of iterators or pointers, or splitting the array.
 *
 * Lets use the following abstraction :
 *   - IF distaceList is a sizeOfDistanceList long array of bits
 *   - and we identify all sizeOfDistanceList long numbers with numOfTowns number of bits set
 *   - THEN we iterate thru all sets
 *
 * LIMITATIONS
 *   - sizeOfDistanceList has to be below 32 to avoid mask overflow
 *   - to cover full sizeOfDistanceList range we can expand this solution to use a UINT_MAX / 32 sized
 *     uint32 array as a mask variable.
 * -----
 *
 * @param  uint32 maxDistance: the maximum distance John wants to travel
 * @param  uint32 numOfTowns: the number of towns Mary wants to visit
 * @param  uint32 distaceList: the list of the distances between the towns
 * @param  uint32 sizeOfDistanceList: the number of distances
 * @return sint32: -1 if there no such travel, and the distance otherwise
 */
sint32 bestTravel(uint32 maxDistance, uint32 numOfTowns, uint32 distaceList[], uint32 sizeOfDistanceList){
	uint32 currentDistance = 0u;
	sint32 exitCode = -1;
	uint32 mask = 0u;

	/* See LIMITATIONS in descriptions. */
	if ( 32u > sizeOfDistanceList ){
		mask = (1u << sizeOfDistanceList) - 1u;
	}

	for ( ; 0u < mask; mask-- ){
		if ( numOfTowns == countSetBits( mask ) ){
			currentDistance = calculateMaskedSum( distaceList, mask );

			if ( (currentDistance <= maxDistance) && ((sint32)currentDistance > exitCode) ){
				exitCode = (sint32)currentDistance;
			}
		}
	}

	return exitCode;
}
