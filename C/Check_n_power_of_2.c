#include <stdio.h>

#define true 1
#define false 0
#define absolute(x) (x > 0 ? x : -x)
int main()
{
    short power_of_2;
    long number;
    scanf("%ld",&number);

    //If n is power of 2, then it is a binary string with a 1 followed by n 0s.
    //Then, (n-1) is a binary string of n 1s. AND -ing n &(n-1) is 0 because there is no bit that is set in both these numbers.
    //Let us assume there is a number x not a power of 2 for which x&(x-1) = 0. This means x has atleast 2 bits set.
    //We get x -1 by inverting all bits of x till the first set bit. Now, x&(x-1) != 0, because we get 0s till the first set bit of x and then we
    //get the same bits of x since x and x-1 are same after that. This assures us that x&(x-1) = 0 only if x = 2^k or if x = 0.
    //However, this test gives true even when n = 0. As 0 is only 0s and -1 is only  1s. So, we check if n is not 0 as well.
    //It could, more succinctly be written as (n && !(n&(n-1)) ), but writing the way I did makes the logic a bit clearer
    number = absolute(number);
    power_of_2 = ( number != 0 && (number&(number-1) ) == 0) ? true : false;

    printf(power_of_2 ? "True\n" : "False\n");
    return 0;
}
