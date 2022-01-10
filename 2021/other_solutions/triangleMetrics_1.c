#include "triangleMetrics.h"
#include "tkp_utils.h"


static float32 determinant(const dtTriangle* Pts);
static float32 perimeterOfTriangle(const dtTriangle* Pts);

/**
 *
 * It defines the determinant of the given matrices which represents the triangle.
 *
 * @param  dtTriangle* triangle: point to the variable which contains the coordinates of the input triangle.
 * @return float32 the calculated determinant of the given matrices which represents the triangle.
 */
static float32 determinant(const dtTriangle* Pts)
{
   return(((float32)Pts->A.X * (float32)Pts->B.Y) +
          ((float32)Pts->A.Y * (float32)Pts->C.X) +
          ((float32)Pts->B.X * (float32)Pts->C.Y))-
         (((float32)Pts->B.Y * (float32)Pts->C.X) +
          ((float32)Pts->A.Y * (float32)Pts->B.X) +
          ((float32)Pts->A.X * (float32)Pts->C.Y));

}

/**
 *
 * It defines the perimeter of the given triangle
 *
 * @param  dtTriangle* triangle: point to the variable which contains the coordinates of the input triangle.
 * @return float32 the calculated perimeter of the given triangle.
 */
static float32 perimeterOfTriangle(const dtTriangle* Pts)
{
    float32 vect1_1en_sq = (((float32)Pts->A.X - (float32)Pts->B.X)* ((float32)Pts->A.X - (float32)Pts->B.X)) + (((float32)Pts->A.Y - (float32)Pts->B.Y)* ((float32)Pts->A.Y - (float32)Pts->B.Y));
    float32 vect2_1en_sq = (((float32)Pts->A.X - (float32)Pts->C.X)* ((float32)Pts->A.X - (float32)Pts->C.X)) + (((float32)Pts->A.Y - (float32)Pts->C.Y)* ((float32)Pts->A.Y - (float32)Pts->C.Y));
    float32 vect3_1en_sq = (((float32)Pts->C.X - (float32)Pts->B.X)* ((float32)Pts->C.X - (float32)Pts->B.X)) + (((float32)Pts->C.Y - (float32)Pts->B.Y)* ((float32)Pts->C.Y - (float32)Pts->B.Y));

    float32 vect1_1en    = tkp_sqrtf(vect1_1en_sq);
    float32 vect2_1en    = tkp_sqrtf(vect2_1en_sq);
    float32 vect3_1en    = tkp_sqrtf(vect3_1en_sq);

    return vect1_1en + vect2_1en + vect3_1en;
}

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
    dtTriangleMetrics retVal = {0.0f,0.0f}; /*return value initialization*/

    retVal.area = determinant(&triangle);   /*First step of area calculation: define the determinant of the given triangle.*/

    retVal.area = tkp_fabsf(retVal.area);   /*Second step of area calculation: the determinant can be negative which is also a valid area value.*/

    if(retVal.area > 0.0f) /*If the determinant 0 the given points can not construct a triangle*/
    {
        /* When the matrices represents a triangle,
         * the area of the triangle can be calculated with the following formula:
         * area = 1/2* det(M)
         * */
        retVal.area      = 0.5f * retVal.area ;            /*Last step of area calculation: */
        retVal.perimeter = perimeterOfTriangle(&triangle); /*Define the perimeter of the given triangle*/
    }

    return retVal;
}
