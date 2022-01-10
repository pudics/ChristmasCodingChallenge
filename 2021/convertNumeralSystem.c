#include "convertNumeralSystem.h"


/**** MACROS *************************************************************************************/
#define INVALID     (0xFFFFFFFFU)   /* Macro for indicating invalid input */
#define DIVISOR     (10U)           /* Macro for the divisor value */
#define BASE_10     (10U)           /* Macro for numeral system 10 */
#define MULTIPLIER  (10U)           /* Macro for the multiplier value */
/**** END OF MACROS ******************************************************************************/


/**** LOCAL FUNCTION DECLARATIONS ****************************************************************/
static inline uint32 ConvertToDec(uint32 inputBinaryNumber);
static inline uint32 ConvertFromDec(uint8 targetNumeralSystem, uint32 convertedResult);
/**** END OF LOCAL FUNCTION DECLARATIONS *********************************************************/


/**** LOCAL FUNCTION DEFINITIONS *****************************************************************/
/**
 * This function converts the given binary represented number to decimal
 *
 * @param[in]   type: uint32, name: inputBinaryNumber
 * @return      type: uint32
 */
static inline uint32 ConvertToDec(uint32 inputBinaryNumber)
{
    register uint32 base    = 1u;
    register uint32 digit   = 0u;
    register uint32 retVal  = 0u;

    while ((boolean)inputBinaryNumber)          /* Process every digit in the input number */
    {
        digit = inputBinaryNumber % DIVISOR;    /* Get the actual digit from the input */

        if (digit > 1u)                         /* If digit is not binary (1 or 0) return 0xFFFFFFFF immediately */
        {
            retVal = INVALID;
            break;
        }
        else                                    /* If digit is binary then convert it to decimal */
        {
            retVal += base * digit;             /* The decimal number is equal to the sum of binary digits times their power of 2 */
            inputBinaryNumber /= DIVISOR;       /* Division by ten to check the next input digit in the following loop */
            base <<= 1u;                        /* Same as multiply by 2 */
        }
    }

    return retVal;
}

/**
 * This function converts the input decimal number to the given base
 *
 * @param[in]   type: uint8, name: targetNumeralSystem
 * @param[in]   type: uint32, name: convertedResult
 * @return      type: uint32
 */
static inline uint32 ConvertFromDec(uint8 targetNumeralSystem, uint32 convertedResult)
{
    register uint32 base    = 1u;
    register uint32 digit   = 0u;
    register uint32 retVal  = INVALID;

    if (INVALID != convertedResult)                                 /* Check if input is valid */
    {
        if (BASE_10 != targetNumeralSystem)                         /* Check if conversion is needed */
        {
            retVal = 0u;                                            /* Reset return value if the input is valid and the target numeral system is not decimal */

            do {                                                    /* Convert decimal number to the given base */
                digit = convertedResult % targetNumeralSystem;      /* Get the remainder as the rightmost digit (least significant digit) of new base number */
                convertedResult /= targetNumeralSystem;             /* Divide the decimal number to be converted by the value of the new base */
                retVal += digit * base;                             /* The destination base digits are the sum of the calculated remainders */
                base *= MULTIPLIER;                                 /* Base is multiplied by ten in every cycle to handle the position of the digits */
            } while ((boolean)convertedResult);                     /* Process every digit in the input number */
        }
        else                                                        /* No need to convert decimal numbers, because they are already converted */
        {
            retVal = convertedResult;
        }
    }

    return retVal;
}
/**** END OF LOCAL FUNCTION DEFINITIONS **********************************************************/


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
    return ConvertFromDec(targetNumeralSystem, ConvertToDec(inputBinaryNumber));    /* First the binary number is converted to decimal after that to the given base, then return */
}
