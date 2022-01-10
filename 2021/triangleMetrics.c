#include "triangleMetrics.h"


/**** MACROS *************************************************************************************/
/* Macros to simplify the view of the source code */
#define Ax          (triangle.A.X)
#define Bx          (triangle.B.X)
#define Cx          (triangle.C.X)
#define Ay          (triangle.A.Y)
#define By          (triangle.B.Y)
#define Cy          (triangle.C.Y)
#define Ax_FLOAT    ((float32)Ax)
#define Bx_FLOAT    ((float32)Bx)
#define Cx_FLOAT    ((float32)Cx)
#define Ay_FLOAT    ((float32)Ay)
#define By_FLOAT    ((float32)By)
#define Cy_FLOAT    ((float32)Cy)

#define INVALID     (0)             /* Invalid triangle macro */

/**
 *  The x86 platform includes a discrete execution unit that is capable of performing floating-point arithmetic (x87 FPU)
 *  FSQRT - Square Root Reference: Intel 64 and IA-32 Architectures Software Developer's Manual
 *
 *  Instruction FSQRT: Computes the square root of the source value in the ST(0) register and stores the result in ST(0)
 *  This instruction's operation is the same in non-64-bit modes and 64-bit mode.
 *
 *  Output operand: result
 *  Input operand: x
 *
 *  Constraint 't': Top of 80387 floating-point stack (ST(0))
 *  Constraint '0': Occupy the same location as output operand 0
 *
 *  Constraint modifier '=': Means that this operand is written to by this instruction: the previous value is discarded and replaced by new data
 */
#define ASM_FSQRT   { __asm( "fsqrt;" : "=t"(result) : "0"(x) ); }   /* Macro created to eliminate MISRA violation (MISRA C 2004, 2.1 - Assembly language shall be encapsulated and isolated) */
/**** END OF MACROS ******************************************************************************/


/**** LOCAL FUNCTION DECLARATIONS ****************************************************************/
static inline float32 getFloatAbsValue(float32 x);
static inline float32 x87_floatSqrt(float32 x);
/**** END OF LOCAL FUNCTION DECLARATIONS *********************************************************/


/**** LOCAL FUNCTION DEFINITIONS *****************************************************************/
/**
 * This function returns the absolute value of the given floating point number
 *
 * @param[in]   type: float32, name: x
 * @return      type: float32
 */
static inline float32 getFloatAbsValue(float32 x)
{
    return (x > 0.0f) ? x : -x;
}

/**
 * This function returns the square root of the given floating point number
 *
 * @param[in]   type: float32, name: x
 * @return      type: float32
 */
static inline float32 x87_floatSqrt(float32 x)
{
    float32 result = 0.0f;

    /*
     * Inline assembly: We use "=t" constraint since we are returning the result at the top of the floating point stack in ST(0),
     * and the "0"(x) constraint says we will pass in 'x' in the same register as parameter 0, which in this case is the top of the floating point stack
     * Similar to "result = ASM_FSQRT(x)"
     */
    ASM_FSQRT

    return result;
}
/**** END OF LOCAL FUNCTION DEFINITIONS **********************************************************/


/**
 * The triangleMetrics function calculates the perimeter and area of the triangle defined by the three input coordinates
 * (the coordinates represent the three vertices of the triangle, and are interpreted in a Descartes coordinate system).
 * If A, B and C are collinear or at least two points are identical, then the return value shall be {0.0f, 0.0f}.
 * The coordinate system is interpreted between -30000 and 30000 in both directions.
 *
 * @param  dtTriangle triangle: contains the coordinates of the input triangle
 * @return dtTriangleMetrics: the calculated perimeter and area of the input triangle
 */
dtTriangleMetrics triangleMetrics(dtTriangle triangle)
{
    dtTriangleMetrics retVal = { 0.0f, 0.0f };  /* Return value of the calculated perimeter and area of the input triangle */

    sint32 term1 = Ax * (By - Cy);              /*              |x1 y1 1|   */
    sint32 term2 = Bx * (Cy - Ay);              /* Area = 1/2 * |x2 y2 1|   */
    sint32 term3 = Cx * (Ay - By);              /*              |x3 y3 1|   */

    if ((term1 + term2 + term3) != INVALID)     /* If three points A(x1,y1), B(x2,y2), and C(x3,y3) are collinear, then x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2) = 0 */
    {
        float32 distanceAB = x87_floatSqrt(((Bx_FLOAT - Ax_FLOAT) * (Bx_FLOAT - Ax_FLOAT)) + ((By_FLOAT - Ay_FLOAT) * (By_FLOAT - Ay_FLOAT)));  /* Calculate distance between A and B vertices */
        float32 distanceBC = x87_floatSqrt(((Bx_FLOAT - Cx_FLOAT) * (Bx_FLOAT - Cx_FLOAT)) + ((By_FLOAT - Cy_FLOAT) * (By_FLOAT - Cy_FLOAT)));  /* Calculate distance between B and C vertices */
        float32 distanceCA = x87_floatSqrt(((Cx_FLOAT - Ax_FLOAT) * (Cx_FLOAT - Ax_FLOAT)) + ((Cy_FLOAT - Ay_FLOAT) * (Cy_FLOAT - Ay_FLOAT)));  /* Calculate distance between C and A vertices */

        retVal.perimeter = distanceAB + distanceBC + distanceCA;                                    /* Adding the length of all the sides, which were calculated above using the formula: dist = sqrt((x2 - x1)^2 + (y2 - y1)^2) */
        retVal.area = getFloatAbsValue(((float32)term1 + (float32)term2 + (float32)term3) * 0.5f);  /* Area of triangle by Determinant method, formula: Area = (1/2) |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)| */
    }

    return retVal;                              /* Return the calculated perimeter and area of the given triangle */
}
