#include "primeGap.h"


static boolean primeCheck(uint32 num);
static uint32 findNextPrime(uint32 startNum);
static uint32 findNextPrimeIndex(uint32 startNum);

/* Table contains the first 1000 prime numbers. The algorithm is the fastest when the given limits are smaller than
 * the 1000. prime (7919), and the slowest when the given limits are above the square of the 1000. prime (62 710 561) */
static uint32 first1000primes[1000] =                                                        \
{                                                                                            \
       2u,      3u,      5u,      7u,     11u,     13u,     17u,     19u,     23u,     29u,  \
      31u,     37u,     41u,     43u,     47u,     53u,     59u,     61u,     67u,     71u,  \
      73u,     79u,     83u,     89u,     97u,    101u,    103u,    107u,    109u,    113u,  \
     127u,    131u,    137u,    139u,    149u,    151u,    157u,    163u,    167u,    173u,  \
     179u,    181u,    191u,    193u,    197u,    199u,    211u,    223u,    227u,    229u,  \
     233u,    239u,    241u,    251u,    257u,    263u,    269u,    271u,    277u,    281u,  \
     283u,    293u,    307u,    311u,    313u,    317u,    331u,    337u,    347u,    349u,  \
     353u,    359u,    367u,    373u,    379u,    383u,    389u,    397u,    401u,    409u,  \
     419u,    421u,    431u,    433u,    439u,    443u,    449u,    457u,    461u,    463u,  \
     467u,    479u,    487u,    491u,    499u,    503u,    509u,    521u,    523u,    541u,  \
     547u,    557u,    563u,    569u,    571u,    577u,    587u,    593u,    599u,    601u,  \
     607u,    613u,    617u,    619u,    631u,    641u,    643u,    647u,    653u,    659u,  \
     661u,    673u,    677u,    683u,    691u,    701u,    709u,    719u,    727u,    733u,  \
     739u,    743u,    751u,    757u,    761u,    769u,    773u,    787u,    797u,    809u,  \
     811u,    821u,    823u,    827u,    829u,    839u,    853u,    857u,    859u,    863u,  \
     877u,    881u,    883u,    887u,    907u,    911u,    919u,    929u,    937u,    941u,  \
     947u,    953u,    967u,    971u,    977u,    983u,    991u,    997u,   1009u,   1013u,  \
    1019u,   1021u,   1031u,   1033u,   1039u,   1049u,   1051u,   1061u,   1063u,   1069u,  \
    1087u,   1091u,   1093u,   1097u,   1103u,   1109u,   1117u,   1123u,   1129u,   1151u,  \
    1153u,   1163u,   1171u,   1181u,   1187u,   1193u,   1201u,   1213u,   1217u,   1223u,  \
    1229u,   1231u,   1237u,   1249u,   1259u,   1277u,   1279u,   1283u,   1289u,   1291u,  \
    1297u,   1301u,   1303u,   1307u,   1319u,   1321u,   1327u,   1361u,   1367u,   1373u,  \
    1381u,   1399u,   1409u,   1423u,   1427u,   1429u,   1433u,   1439u,   1447u,   1451u,  \
    1453u,   1459u,   1471u,   1481u,   1483u,   1487u,   1489u,   1493u,   1499u,   1511u,  \
    1523u,   1531u,   1543u,   1549u,   1553u,   1559u,   1567u,   1571u,   1579u,   1583u,  \
    1597u,   1601u,   1607u,   1609u,   1613u,   1619u,   1621u,   1627u,   1637u,   1657u,  \
    1663u,   1667u,   1669u,   1693u,   1697u,   1699u,   1709u,   1721u,   1723u,   1733u,  \
    1741u,   1747u,   1753u,   1759u,   1777u,   1783u,   1787u,   1789u,   1801u,   1811u,  \
    1823u,   1831u,   1847u,   1861u,   1867u,   1871u,   1873u,   1877u,   1879u,   1889u,  \
    1901u,   1907u,   1913u,   1931u,   1933u,   1949u,   1951u,   1973u,   1979u,   1987u,  \
    1993u,   1997u,   1999u,   2003u,   2011u,   2017u,   2027u,   2029u,   2039u,   2053u,  \
    2063u,   2069u,   2081u,   2083u,   2087u,   2089u,   2099u,   2111u,   2113u,   2129u,  \
    2131u,   2137u,   2141u,   2143u,   2153u,   2161u,   2179u,   2203u,   2207u,   2213u,  \
    2221u,   2237u,   2239u,   2243u,   2251u,   2267u,   2269u,   2273u,   2281u,   2287u,  \
    2293u,   2297u,   2309u,   2311u,   2333u,   2339u,   2341u,   2347u,   2351u,   2357u,  \
    2371u,   2377u,   2381u,   2383u,   2389u,   2393u,   2399u,   2411u,   2417u,   2423u,  \
    2437u,   2441u,   2447u,   2459u,   2467u,   2473u,   2477u,   2503u,   2521u,   2531u,  \
    2539u,   2543u,   2549u,   2551u,   2557u,   2579u,   2591u,   2593u,   2609u,   2617u,  \
    2621u,   2633u,   2647u,   2657u,   2659u,   2663u,   2671u,   2677u,   2683u,   2687u,  \
    2689u,   2693u,   2699u,   2707u,   2711u,   2713u,   2719u,   2729u,   2731u,   2741u,  \
    2749u,   2753u,   2767u,   2777u,   2789u,   2791u,   2797u,   2801u,   2803u,   2819u,  \
    2833u,   2837u,   2843u,   2851u,   2857u,   2861u,   2879u,   2887u,   2897u,   2903u,  \
    2909u,   2917u,   2927u,   2939u,   2953u,   2957u,   2963u,   2969u,   2971u,   2999u,  \
    3001u,   3011u,   3019u,   3023u,   3037u,   3041u,   3049u,   3061u,   3067u,   3079u,  \
    3083u,   3089u,   3109u,   3119u,   3121u,   3137u,   3163u,   3167u,   3169u,   3181u,  \
    3187u,   3191u,   3203u,   3209u,   3217u,   3221u,   3229u,   3251u,   3253u,   3257u,  \
    3259u,   3271u,   3299u,   3301u,   3307u,   3313u,   3319u,   3323u,   3329u,   3331u,  \
    3343u,   3347u,   3359u,   3361u,   3371u,   3373u,   3389u,   3391u,   3407u,   3413u,  \
    3433u,   3449u,   3457u,   3461u,   3463u,   3467u,   3469u,   3491u,   3499u,   3511u,  \
    3517u,   3527u,   3529u,   3533u,   3539u,   3541u,   3547u,   3557u,   3559u,   3571u,  \
    3581u,   3583u,   3593u,   3607u,   3613u,   3617u,   3623u,   3631u,   3637u,   3643u,  \
    3659u,   3671u,   3673u,   3677u,   3691u,   3697u,   3701u,   3709u,   3719u,   3727u,  \
    3733u,   3739u,   3761u,   3767u,   3769u,   3779u,   3793u,   3797u,   3803u,   3821u,  \
    3823u,   3833u,   3847u,   3851u,   3853u,   3863u,   3877u,   3881u,   3889u,   3907u,  \
    3911u,   3917u,   3919u,   3923u,   3929u,   3931u,   3943u,   3947u,   3967u,   3989u,  \
    4001u,   4003u,   4007u,   4013u,   4019u,   4021u,   4027u,   4049u,   4051u,   4057u,  \
    4073u,   4079u,   4091u,   4093u,   4099u,   4111u,   4127u,   4129u,   4133u,   4139u,  \
    4153u,   4157u,   4159u,   4177u,   4201u,   4211u,   4217u,   4219u,   4229u,   4231u,  \
    4241u,   4243u,   4253u,   4259u,   4261u,   4271u,   4273u,   4283u,   4289u,   4297u,  \
    4327u,   4337u,   4339u,   4349u,   4357u,   4363u,   4373u,   4391u,   4397u,   4409u,  \
    4421u,   4423u,   4441u,   4447u,   4451u,   4457u,   4463u,   4481u,   4483u,   4493u,  \
    4507u,   4513u,   4517u,   4519u,   4523u,   4547u,   4549u,   4561u,   4567u,   4583u,  \
    4591u,   4597u,   4603u,   4621u,   4637u,   4639u,   4643u,   4649u,   4651u,   4657u,  \
    4663u,   4673u,   4679u,   4691u,   4703u,   4721u,   4723u,   4729u,   4733u,   4751u,  \
    4759u,   4783u,   4787u,   4789u,   4793u,   4799u,   4801u,   4813u,   4817u,   4831u,  \
    4861u,   4871u,   4877u,   4889u,   4903u,   4909u,   4919u,   4931u,   4933u,   4937u,  \
    4943u,   4951u,   4957u,   4967u,   4969u,   4973u,   4987u,   4993u,   4999u,   5003u,  \
    5009u,   5011u,   5021u,   5023u,   5039u,   5051u,   5059u,   5077u,   5081u,   5087u,  \
    5099u,   5101u,   5107u,   5113u,   5119u,   5147u,   5153u,   5167u,   5171u,   5179u,  \
    5189u,   5197u,   5209u,   5227u,   5231u,   5233u,   5237u,   5261u,   5273u,   5279u,  \
    5281u,   5297u,   5303u,   5309u,   5323u,   5333u,   5347u,   5351u,   5381u,   5387u,  \
    5393u,   5399u,   5407u,   5413u,   5417u,   5419u,   5431u,   5437u,   5441u,   5443u,  \
    5449u,   5471u,   5477u,   5479u,   5483u,   5501u,   5503u,   5507u,   5519u,   5521u,  \
    5527u,   5531u,   5557u,   5563u,   5569u,   5573u,   5581u,   5591u,   5623u,   5639u,  \
    5641u,   5647u,   5651u,   5653u,   5657u,   5659u,   5669u,   5683u,   5689u,   5693u,  \
    5701u,   5711u,   5717u,   5737u,   5741u,   5743u,   5749u,   5779u,   5783u,   5791u,  \
    5801u,   5807u,   5813u,   5821u,   5827u,   5839u,   5843u,   5849u,   5851u,   5857u,  \
    5861u,   5867u,   5869u,   5879u,   5881u,   5897u,   5903u,   5923u,   5927u,   5939u,  \
    5953u,   5981u,   5987u,   6007u,   6011u,   6029u,   6037u,   6043u,   6047u,   6053u,  \
    6067u,   6073u,   6079u,   6089u,   6091u,   6101u,   6113u,   6121u,   6131u,   6133u,  \
    6143u,   6151u,   6163u,   6173u,   6197u,   6199u,   6203u,   6211u,   6217u,   6221u,  \
    6229u,   6247u,   6257u,   6263u,   6269u,   6271u,   6277u,   6287u,   6299u,   6301u,  \
    6311u,   6317u,   6323u,   6329u,   6337u,   6343u,   6353u,   6359u,   6361u,   6367u,  \
    6373u,   6379u,   6389u,   6397u,   6421u,   6427u,   6449u,   6451u,   6469u,   6473u,  \
    6481u,   6491u,   6521u,   6529u,   6547u,   6551u,   6553u,   6563u,   6569u,   6571u,  \
    6577u,   6581u,   6599u,   6607u,   6619u,   6637u,   6653u,   6659u,   6661u,   6673u,  \
    6679u,   6689u,   6691u,   6701u,   6703u,   6709u,   6719u,   6733u,   6737u,   6761u,  \
    6763u,   6779u,   6781u,   6791u,   6793u,   6803u,   6823u,   6827u,   6829u,   6833u,  \
    6841u,   6857u,   6863u,   6869u,   6871u,   6883u,   6899u,   6907u,   6911u,   6917u,  \
    6947u,   6949u,   6959u,   6961u,   6967u,   6971u,   6977u,   6983u,   6991u,   6997u,  \
    7001u,   7013u,   7019u,   7027u,   7039u,   7043u,   7057u,   7069u,   7079u,   7103u,  \
    7109u,   7121u,   7127u,   7129u,   7151u,   7159u,   7177u,   7187u,   7193u,   7207u,  \
    7211u,   7213u,   7219u,   7229u,   7237u,   7243u,   7247u,   7253u,   7283u,   7297u,  \
    7307u,   7309u,   7321u,   7331u,   7333u,   7349u,   7351u,   7369u,   7393u,   7411u,  \
    7417u,   7433u,   7451u,   7457u,   7459u,   7477u,   7481u,   7487u,   7489u,   7499u,  \
    7507u,   7517u,   7523u,   7529u,   7537u,   7541u,   7547u,   7549u,   7559u,   7561u,  \
    7573u,   7577u,   7583u,   7589u,   7591u,   7603u,   7607u,   7621u,   7639u,   7643u,  \
    7649u,   7669u,   7673u,   7681u,   7687u,   7691u,   7699u,   7703u,   7717u,   7723u,  \
    7727u,   7741u,   7753u,   7757u,   7759u,   7789u,   7793u,   7817u,   7823u,   7829u,  \
    7841u,   7853u,   7867u,   7873u,   7877u,   7879u,   7883u,   7901u,   7907u,   7919u   \
};


/*
 * Returns the index of the first prime number found in 'first1000primes' from @startNum (@startNum included)
 *
 * @param  uint32 startNum: number from which the search is started, assumed that <= 7919
 * @return uint32: index of the first prime found
 */
static uint32 findNextPrimeIndex(uint32 startNum)
{
    uint32 index = 900u;    /* Index of the prime table */

    /* Firstly, narrowing the search to 100 numbers */
    while (startNum < first1000primes[index])
    {
        index -= 100u;
    }

    /* Secondly, finding the exact number */
    while (startNum > first1000primes[index])
    {
        index++;
    }

    /* Return the index of the found number */
    return index;
}


/*
 * Checks whether @num is a prime or not
 *
 * @param  uint32 num: number to be checked
 * @return boolean: TRUE if @num is prime, FALSE if not
 */
static boolean primeCheck(uint32 num)
{
    boolean retVal = TRUE;    /* return value */
    uint32 i;                 /* cycle counter / prime index */

    /* A number is a prime if it is only divisible by 1 and itself. Mathematically it is enough to check
     * the divisibility by other primes that are lower than the square root of the number. */

    /* Check whether @num is within the range of the first 1000 primes */
    if (num <= first1000primes[999])
    {
        /* If the prime found with the result of 'findNextPrimeIndex' is not equal to @num,
         * it means that @num is not part of 'first1000primes', so it is not a prime */
        if ( num != first1000primes[findNextPrimeIndex(num)] )
        {
            retVal = FALSE;
        }
    }
    /* @num is not within the range of the first 1000 primes, another algorithm shall be used */
    else
    {
        /* Check the divisibility by the first 1000 primes. If the square root of @num is reached, it means
         * that @num is not a prime and the algorithm can be stopped */
        for (i = 0u; ((first1000primes[i] * first1000primes[i]) < num) && (i < 1000u); i++)
        {
            /* If @num is divisible by any primes, it means it is not a prime and the algorithm can be stopped */
            if (0u == (num % first1000primes[i]))
            {
                retVal = FALSE;
                break;
            }
        }

        /* At this point 'i = 1000' means, that no divider was found within the first 1000 primes, and the square root of
         * @num was not reached yet. The prime table cannot be used anymore, so the search shall be continued
         * with a more complex algorithm:
         * Every 'n' number can be written in the format 'n = 6*i+k' where 'k = n % 6', so 'k = 0, 1, 2, 3, 4 or 5'.
         * Since 6*i+0, 6*i+2 and 6*i+4 are divisible by 2, and 6*i+3 is divisible by 3, only 6*i+1 and 6*i+5 can be primes.
         * Therefore a 'n' number is a potential prime only if 'n % 6 = 1 or 5', with the exception of 2 and 3. It means,
         * that all the potential primes have a format of '6*i+1' or '6*i+5' when 'i >= 1'. Therefore it is enough to
         * check only 2 numbers out of every 6 numbers, which significantly improves run time. */
        if (1000u == i)
        {
            /* According to the above described algorithm, divisibility of @num is not checked for every number,
             * but only for the potential prime numbers (Ideally only the prime numbers should be checked).
             * The loop should be started from 7920 as it is the first number that is greater than the 1000. prime
             * and divisible by 6 */
            for (i = 7920u; (i*i) < num; i += 6u)
            {
                /* If @num is divisible by any potential primes, it means it is not a prime and the algorithm can be stopped */
                if ( (0u == (num % (i + 1u))) || (0u == (num % (i + 5u))) )
                {
                    retVal = FALSE;
                    break;
                }
            }
        }
    }

    /* return the result */
    return retVal;
}


/*
 * Returns the first prime number found from @startNum (@startNum included).
 * This function is only called if the prime table cannot be used, so when @startNum > 7919
 *
 * @param  uint32 startNum: number from which the search is started, assumed that > 7919
 * @return uint32: the first prime found
 */
static uint32 findNextPrime(uint32 startNum)
{
    uint32 retVal = 0u;          /* return value */
    uint32 mod = startNum % 6u;  /* startNum % 6 is calculated here once to spare some runtime */

    /* The principle here is the same as described in function 'primeCheck', so only the potential primes are checked
     * whether they are real primes or not in order to spare runtime. The algorithm shall be started from a number
     * which has 0 as modulo 6, therefore some adjustments has to be made at the beginning. */

    /* When modulo is already 0 */
    if (0u == mod)
    {
        /* Nothing to do, the algorithm can be started from @startNum,
         * so the potential primes are @startNum + 1,  @startNum + 5 etc.*/
    }
    /* When modulo is 1 */
    else if (1u == mod)
    {
        /* The algorithm should be started from @startNum - 1,
         * since the potential primes are @startNum,  @startNum + 4 etc.*/
        startNum--;
    }
    /* When modulo is 2, 3, 4 or 5 */
    else
    {
        /* If the algorithm is started from '@startNum - mod' (like in previous branch) than the first '6*i+1'
         * potential prime would be smaller than @startNum. To prevent returning this smaller prime,
         * the loop is started from the next number that is divisible by 6 ( 6*(i+1) ), so from '@startNum - mod + 6',
         * and the skipped first '6*i+5' potential prime is tested manually outside the loop. */

        /* Setting @startNum for the first '6*i+5' potential prime */
        startNum = (startNum - mod) + 5u;

        /* Checking the first potential prime '@startNum - mod + 5' */
        if (TRUE == primeCheck(startNum))
        {
            /* The tested number is a prime, it can be returned */
            retVal = startNum;
        }
        else
        {
            /* Increment @startNum to set '@startNum - mod + 6' as the start of the loop */
            startNum++;
        }
    }

    /* Checking only the potential primes as described in 'primeCheck' function whether they are real primes or not */
    while (0u == retVal)
    {
        /* Checking the '6*i+1' potential prime */
        if (TRUE == primeCheck(startNum + 1u))
        {
            retVal = startNum + 1u;
        }
        /* Checking the '6*i+5' potential prime */
        else if (TRUE == primeCheck(startNum + 5u))
        {
            retVal = startNum + 5u;
        }
        /* Increment @startNum for the next cycle */
        else
        {
            startNum += 6u;
        }
    }

    /* Return the first prime found */
    return retVal;
}


/**
 * The primeGap function calculates the first pair of two prime numbers spaced
 * with gap between the limits lowLimit, highLimit if these numbers exist.
 */
void primeGap(uint16 gap, uint32 lowLimit, uint32 highLimit, uint32 result[])
{
    uint32 firstPrime;    /* Temporary variable for the first prime in the row */
    uint32 secondPrime;   /* Temporary variable for the second prime in the row */
    uint32 index;         /* Index of the prime table */

    /* Set @result to the default values */
    result[0] = 0u;
    result[1] = 0u;

    /* Find the first prime in the row.
     * If @lowLimit is within the range of the first 1000 primes, then the firstPrime is
     * searched from the prime table. */
    if (lowLimit <= first1000primes[999])
    {
        index = findNextPrimeIndex(lowLimit);
        firstPrime = first1000primes[index];
    }
    /* Otherwise, the more complex algorithm is used. */
    else
    {
        firstPrime = findNextPrime(lowLimit);
    }

    /* Main loop of the algorithm.
     * The firstPrime should be smaller or equal to @highLimit at least by @gap, otherwise the appropriate secondPrime
     * would be outside the limits. The loop may exit earlier within the cycle if the appropriate primes are found. */
    while (firstPrime <= (highLimit - gap))
    {
        /* Find the second prime in the row.
         * If 'index < 999', it means that the second prime is also part of the prime table, so it is search from there */
        if (index < 999u)
        {
            index++;
            secondPrime = first1000primes[index];
        }
        /* Otherwise, the more complex algorithm is used. */
        else
        {
            secondPrime = findNextPrime(firstPrime + 2u);
        }

        /* If the gap between the primes equal to @gap, then exit the loop and return these primes */
        if ((secondPrime - firstPrime) == gap)
        {
            result[0] = firstPrime;
            result[1] = secondPrime;
            break;
        }
        /* Otherwise, set the secondPrime as the firstPrime for the next cycle */
        else
        {
            firstPrime = secondPrime;
        }
    }
}
