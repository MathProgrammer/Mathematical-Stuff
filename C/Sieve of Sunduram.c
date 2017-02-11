#include <stdio.h>
#include <stdlib.h>
#define target 110000

//Function prototypes
void initial_marking(long int[]);
void marking(long int[]);
void make_prime_list(long int[],long int[]);
void print_primes(long int[]);

/*Every integer can be written in the form 2^i*v where v is odd.
This algorithm generates a list of numbers that are only odd.
We want to ensure that all the composite odd numbers are marked out.

In the final list, all numbers will be of the form 2^0 v. So, we only need to worry about odd factors.
An odd number will be composite if it is of the form (2i + 1)(2j + 1), where i and j are strictly positive integers.
So, a composite odd number q = 2k + 1 = 4ij + 2i + 2j + 1
This means k = i + j + 2ij.
Whenever k is of the form, i + j + 2ij, 2k+ 1 is composite and whenever an odd integer q is composite, the condition holds for k, q = 2k + 1

All we seek to do is mark all numbers that can be written as i +j + 2ij. And for any unmarked integer k, we know that 2k + 1 will be prime.
Note - We need to hard code 2 since this algorithm 'only' generates the odd primes. */
int main()
{
    //Half of the numbers from 1 to target will be even so the number of primes will never exceed target/2.
    //The algorithm only worries about the first half of the range. That's why list also goes till target/2.
    long list[target/2], primes[target/2];

    //Sieve of Sundaram
    initial_marking(list);
    //Crossing out all numbers of the form i + j + 2ij
    marking(list);

    //Making the list of primes
    make_prime_list(primes, list);

    //Displaying the list
    print_primes(primes);

    return 0;
}

//Initially, everything is marked 1
void initial_marking(long int list[])
{
    int i;

    for(i = 1; i <= target/2; i++)
    {
        list[i] = 1;
    }
}

//Crossing out numbers of the form i + j + 2ij
void marking(long int list[])
{
    long long i, crossed_out_num, cross_limit, increment; //To avoid overflow

    /*f(i,j) = i + j + 2ij
    For a given value of i, the minimum is when j = 1. Minimum is f(i,1) = 3i + 1
    f(i, j + 1) = f(i,j) + 2i + 1 so we only need to increase the value of the crossed number by 2i + 1, instead of updating by one.
    i goes from 1 to target/2. But, f(i,j) starts from 3i + 1. If i is greater than target/6, then f(i,j) is out of range.
    So, the minimum
    Maximum occurs when j = i. f(i,j) = 2i(i+1).
    The last number to be crossed out for a given i is either 2i(i + 1) or the last f(i,j) before target/2, whichever comes first.*/

	//All numbers of the form i + j + 2ij need to be marked out

    for(i = 1; i <= target/6; i++)
    {
        increment = 2*i + 1;
        cross_limit = 2*i*(i + 1);

        if(cross_limit > target/2)
        {
            cross_limit = target/2;
        }

        for(crossed_out_num = 3*i + 1;crossed_out_num <= cross_limit ; crossed_out_num += increment)
        {
            list[crossed_out_num] = 0;
        }
    }
}

//Making the list of primes
void make_prime_list(long int primes[],long int list[])
{
    int i = 0, primeCount = 0;

    //We need to put 2 in ourselves because the algorithm 'only' generates all the odd primes
    primes[primeCount++] = 2;
    for(i = 1; i <= target/2; i++)
    {
        //Checking if the number is not crossed out and adding 2i + 1 to the list if it is unmarked.
        if(list[i] == 1)
        {
            primes[primeCount++] = (2*i + 1);
        }
    }

    //Putting 0 to mark the end of the array
    primes[primeCount] = 0;
}

void print_primes(long int primes[])
{
    int i;

    //0 indicates the end of the array
    for(i = 0; primes[i] != 0; i++)
    {
        printf("%ld\t",primes[i]);
    }
}
