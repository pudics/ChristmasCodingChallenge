#include "bestTravel.h"


#define STACK_RESERVE	100000u			/* constant used to ensure proper stack size - counting in u32 */
#define STACKSIZE_PER_EXECUTION	10u		/* size of stack needed for a single execution of the recursive function, in u32 words */
#define ALLOWABLE_EXECUTIONS	(STACK_RESERVE / STACKSIZE_PER_EXECUTION)	/* Maximum allowed execution before risk of stack overflow */

static uint32 execCnt = 0u;	/*  Execution counter keeps tracking how many times recursive function was executed, terminates process if not plausible */
static uint32 recursionLimit = 0u;	/* Plausibility limit for number of recusrions */

static uint32 fact(uint32 n);
static uint32 nChooseK(uint32 n, uint32 k);
static sint32 getClosestMatch(uint32 maxDistance, uint32 numOfTowns, uint32 distanceList[], uint32 sizeOfDistanceList, uint32 initialDistance);
static void setupRecursiveDefense(uint32 sizeOfDistanceList, uint32 numOfTowns);


/**
 * Utility function returning the factorial of n
 */
static uint32 fact(uint32 n)
{
	uint32 retVal = 1u;
	for(uint32 i = 2u; i <= n; i++)
	{
		retVal *= i;
	}
    return retVal;
}

/**
 * Utility function returning the number of combinations without repetition (n choose k)
 */
static uint32 nChooseK(uint32 n, uint32 k)
{
	return fact(n)/(fact(k)* fact(n - k));
}

/**
 * The getClosestMatch function calculates the closest  match assuming an already existing initial distance - or returns -1
 *
 * @param  uint32 maxDistance: the maximum distance John wants to travel
 * @param  uint32 numOfTowns: the number of towns Mary wants to visit
 * @param  uint32 distaceList: the list of the distances between the towns
 * @param  uint32 sizeOfDistanceList: the number of distances
 * @param  uint32 initialDistance: the initial distance already made
 * @return sint32: -1 if there no such travel, and the distance otherwise
 */
static sint32 getClosestMatch(uint32 maxDistance, uint32 numOfTowns, uint32 distanceList[], uint32 sizeOfDistanceList, uint32 initialDistance)
{
	sint32 retVal = -1;			/* Initially we assume that no valid distance will be found - it is overwritten when proven differently */
	sint32 currDistance = 0;

	/* Defensive check against recursion termination error */
	execCnt++;
	if(execCnt > recursionLimit)
	{
	  retVal = -2;				/* Recusrions limit is exceeded - terminate all occurrences immediately  */
	} else if(0u == numOfTowns) 	/* recursion exit condition - if no more city is needed, just return current distance or -1 */
	{
		retVal = (maxDistance < initialDistance) ? -1 : (sint32)initialDistance;
	}
	else						/* Warning! Black alert! Recusrion is in progress! */
	{
		/* Iterate through section of list and find closest match */
		for(uint16 i = 0u; i <= (sizeOfDistanceList - numOfTowns); i++)
		{
			currDistance = getClosestMatch(	/* parasoft-suppress MISRA2004-16_2 "Intentional MISRA violation: recursion is used, but safe, because
											 * (i) exit condition is simple, comparsion of a constant quantitiy and
											 * a strictly monotonously inreasing quantity - set at invocation
											 * (ii) Worst case execution number for recursive function is calculated,
											 * number of executions are counted in static variable, recursive function
											 * immediately terminates with error code if limit is exceeded
											 * (iii) having proper stack size is ensured via a dummy stack array in initgraph
											 * function - can be determined by compiler" */
											maxDistance, 						/* max distance never changes */
											(numOfTowns - 1u), 					/* this execution occurrence binds a city - next one needs to handle one less cities */
											&distanceList[i + 1u], 	/* array passed to next execution occurrence starts from next unhandled element */
											(sizeOfDistanceList - i - 1u), 		/* size is adjusted to reflect shortening of list */
											initialDistance + distanceList[i]);	/* we assume ith element is in the sum - add it to initial distance for next occurrence */
			if(-1 == currDistance)					/* Using ith element we cannot remain in max distance - continue searching with another element */
			{
				;
			} else if((sint32)maxDistance == currDistance)	/* We have found optimal distance, no need to continue searching */
			{
				retVal = currDistance;
				break;
			} else									/* Current distance is valid - update candidate if better than previous ones, but keep on searching for better */
			{
				retVal = (currDistance > retVal) ? currDistance : retVal;
			}
		}
	}
	return retVal;
}

/**
 * setupRecursiveDefense ensures correct stack size setting to compiler as well as initiates check for termination
 * Number of executions (Worst case):
 * - Recursive algorithm with termination condition (city count = 0) is executed ListLength choose CityCount times,
 *   as it is executed eaxactly once per combinations
 * - That is invoked by previous level of executions, but never for the last element -
 *   both list size and elements to choose is reduced by one
 * - That is executed by previous level, with decreased list size and elements to choose...
 *   ... and so on, and so forth
 * --> Worst case execution count is (n k) + (n-1 k-1) + ... + (n-k  0), where n=ListLength, k= CityCount
 */
static void setupRecursiveDefense(uint32 sizeOfDistanceList, uint32 numOfTowns)
 {
	/* Dummy array informing compiler about the maximal size of needed stack space: one execution takes 10*32 bit stack, maximum executions are limited to 10k */
	volatile uint32 dummyArray[STACK_RESERVE];   /* worst case stack size is defined based on engineering stomach */

	execCnt = 0u;		/* Clearing static variable before start of recursion */
	/* Setting recursion limit - number of combinations without repetition, calculated as n choose k...
	*  ...multiplied by numOfTowns, as this many calls are needed worst case to get to one combination
	*/
    recursionLimit = 0u;
    for(uint16 i = 0u; i <= numOfTowns; i++)
    {
        recursionLimit += nChooseK(sizeOfDistanceList - i, numOfTowns - i);
    }
	/* Checking whether reserved stack size is sufficiently big */
	if(ALLOWABLE_EXECUTIONS < recursionLimit)
	{
		/* With the given arguments risk of stack overflow is high - not allowing any executions to trigger abortion */
		recursionLimit = 0u;
	}
 }

/**
 * The bestTravel function calculates the est travel for Mary and John.
 *
 * @param  uint32 maxDistance: the maximum distance John wants to travel
 * @param  uint32 numOfTowns: the number of towns Mary wants to visit
 * @param  uint32 distaceList: the list of the distances between the towns
 * @param  uint32 sizeOfDistanceList: the number of distances
 * @return sint32: -1 if there no such travel, and the distance otherwise
 */
sint32 bestTravel(uint32 maxDistance, uint32 numOfTowns, uint32 distaceList[], uint32 sizeOfDistanceList)
{
	sint32 retVal = 0;
	/* Input checking */
	if(numOfTowns > sizeOfDistanceList)
	{
	    retVal = -1;
	}
	else
	{
	    setupRecursiveDefense(sizeOfDistanceList, numOfTowns);
	    retVal = getClosestMatch(maxDistance, numOfTowns, distaceList, sizeOfDistanceList, 0u);	
	}
	return retVal;
}
