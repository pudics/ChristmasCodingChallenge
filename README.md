# ChristmasCodingChallenge
![CodingChallenge](http://i.imgur.com/0L2EgAE.png)

---
**The aim of the game is to happy code a bit while also improving C coding knowledge. The goal is to create a functionally correct, run-time optimized, misra violation free, clean and understandable code.**

---
## December 2020
### The 1st challenge:
**Prototype of the function:**
sint32 cycle(uint32 inputVal);

**Task:**
Let be inputVal an integer relative prime with 10 (e.g. 7). (Two numbers are relative prime if the only positive integer that evenly divides both of them is 1.)
1/7 = 0.142857 142857 142857 ... We see that the decimal part has a cycle: 142857. The length of this cycle is 6. In the same way:
1/11 = 0.09 09 09 .... Cycle length is 2.
Task: Given an unsigned integer inputVal (inputVal > 1), the function cycle(inputVal) returns the length of the cycle if inputVal and 10 are relative prime, otherwise returns -1.

**Examples:**
* cycle(5) = -1
* cycle(13) = 6 -> 0.076923 076923 0769
* cycle(37) = 3 -> 0.027 027 027 027 027
* cycle(94) = -1

### The 2nd challenge:
**Prototype of the function:**
sint32 digitPower(uint32 num, uint32 exp);
Some numbers have interesting properties. For example:
89 --> 8¹ + 9² = 89 * 1
695 --> 6² + 9³ + 5⁴= 1390 = 695 * 2
46288 --> 4³ + 6⁴+ 2⁵ + 8⁶ + 8⁷ = 2360688 = 46288 * 51

**Task:**
Given a unsigned integer num written as abcd... (a, b, c, d... being digits) and an unsigned integer exp. Note: num and exp are > 0.
We want to find a positive integer k, if it exists, such as the sum of the digits of num taken to the successive powers of exp is equal to k * num.
In other words:
Is there an integer k such as : (a^exp + b^(exp+1) + c^(exp+2) + d^(exp+3) + ...) = n * k
If it is the case we will return k, if not return -1.

**Examples:**
* digitPower(89, 1) = 1
* digitPower(92, 1) = -1
* digitPower(695, 2) = 2
* digitPower(46288, 3) = 51

### The 3rd challenge:
**Prototype of the function:**
void primeGap(uint16 gap, uint32 lowLimit, uint32 highLimit, uint32 result[]);
The prime numbers are not regularly spaced. For example from 2 to 3 the gap is 1. From 3 to 5 the gap is 2. From 7 to 11 it is 4.
Between 2 and 50 we have the following pairs of 2-gaps primes: 3-5, 5-7, 11-13, 17-19, 29-31, 41-43.
A prime gap of length n is a run of n-1 consecutive composite numbers between two successive primes.

**Task:**
Write the function primeGap with parameters:
- gap (>= 2) which indicates the gap we are looking for
- lowLimit (> 2) which gives the start of the search (lowLimit inclusive)
- highLimit (>= lowLimit) which gives the end of the search (highLimit inclusive)
So this function should return the first pair of two prime numbers spaced with gap between the limits lowLimit, highLimit if these numbers exist:
- result[] shall be the return value, result[0] shall store the lower prime, result[1] shall store the higher prime if these primes exist, otherwise [0, 0].

**Examples:**
* primeGap(2, 5, 10, result[]);       --> result[0] = 5,      result[1] = 7
* primeGap(2, 100, 110, result[]);    --> result[0] = 101,    result[1] = 103
* primeGap(4, 100, 110, result[]);    --> result[0] = 103,    result[1] = 107
* primeGap(6, 100, 110, result[]);    --> result[0] = 0,      result[1] = 0

### The 4th challenge:
**Prototype of the function:**
sint32 bestTravel(uint32 maxDistance, uint32 numOfTowns, uint32 distanceList[], uint32 sizeOfDistanceList);

**Task:**
John and Mary want to travel between a few towns A, B, C ... Mary has on a sheet of paper a list of distances between these towns. E.g. distanceList = [50, 55, 57, 58, 60]. John is tired of driving and he says to Mary that he doesn't want to drive more than maxDistance = 174 kilometers and he will visit only numOfTowns = 3 towns.
Which distances, hence which towns, they will choose so that the sum of the distances is the biggest possible to please Mary and John?
Example:
With list distaceList and 3 towns to visit they can make a choice between: [50,55,57],[50,55,58],[50,55,60],[50,57,58],[50,57,60],[50,58,60],[55,57,58],[55,57,60],[55,58,60],[57,58,60].
The sums of distances are then: 162, 163, 165, 165, 167, 168, 170, 172, 173, 175.
The biggest possible sum taking a limit of 174 into account is then 173 and the distances of the 3 corresponding towns is [55, 58, 60].
The function bestTravel will take as parameters maxDistance (maximum sum of distances >= 0), numOfTowns (number of towns to visit >= 1) and distanceList (list of distances, all distances are > 0 and this list has at least one element). The function returns the "best" sum i.e. the biggest possible sum of numOfTowns distances less than or equal to the given limit maxDistance, if that sum exists, or otherwise -1.

**Examples:**
* ts = [50, 55, 56, 57, 58]           bestTravel(163, 3, ts) -> 163
* xs = [50]                           bestTravel(163, 3, xs) -> -1
* ys = [91, 74, 73, 85, 73, 81, 87]   bestTravel(230, 3, ys) -> 228

---
## December 2021
### The 1st challenge:
**Prototype of the function:**
uint8 differentDigits(uint32 inputVal);

**Task:**
Return how many different digits inputVal has!

**Examples:**
* differentDigits(8)      --> 1
* differentDigits(1330)   --> 3
* differentDigits(456789) --> 6

### The 2nd challenge:
**Prototype of the function:**
dtTriangleMetrics triangleMetrics(dtTriangle triangle);	/* For details about the applied data types please check the prepared component or online environment. */

**Task:**
The triangleMetrics function calculates the perimeter and area of the triangle defined by the three input coordinates (the coordinates A, B and C represent the three vertices of the triangle, and are interpreted in a Descartes coordinate system). If A, B and C are collinear or at least two points are identical, then the return value shall be {0.0f, 0.0f}. The coordinate system is interpreted between -30000 and 30000 in both directions.
The required accuracy is 0.01.

**Examples:**
* triangleMetrics({{0, 0}, {0, 1}, {1, 0}})   --> perimeter = 3.41, area: 0.5
* triangleMetrics({{3, 2}, {3, -2}, {6, 2}})  --> perimeter = 12.0, area: 6.0
* triangleMetrics({{-3, 2}, {1, 1}, {5, 0}})  --> perimeter = 0.0, area: 0.0

### The 3rd challenge:
**Prototype of the function:**
uint32 convertNumeralSystem(uint32 inputBinaryNumber, uint8 targetNumeralSystem);

**Task:**
The inputBinaryNumber shall be interpreted as a binary number (so the largest valid input is 1111111111). The function shall return with the base-targetNumeralSystem converted value of the inputBinaryNumber.
The targetNumeralSystem may be assumed to be in range [3, 10].
If inputBinaryNumber contains other digits than 0 and 1, then return value shall be 0xFFFFFFFF.

**Examples:**
* convertNumeralSystem(101, 10)       --> 5
* convertNumeralSystem(1011, 3)       --> 102
* convertNumeralSystem(1100111, 7)    --> 205
* convertNumeralSystem(1100111, 8)    --> 147
* convertNumeralSystem(8, 4)          --> 0xFFFFFFFF (4294967295)
