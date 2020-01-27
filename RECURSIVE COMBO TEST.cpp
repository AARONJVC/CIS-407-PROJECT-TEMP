#include<stdio.h>

//factorial method
//actually negatives are ok but don't anyway
int fact(int n)
{
    int result = 1; //0!

    for(int i = n; i > 0; i--)
    {
        result *= i;
    }

    return result;
}

//Can't have k greater than n
//this combinatoric method will help me find an efficient data storage encoding in the pixels (I hope)
int choose(int n, int k)
{
    //pigeonhole principle!
    if(k > n)
    {
        return -1;
    }

    int m = n - k;

    int j = fact(k);

    int result = 1;

    //modify the range to avoid calculating 3 factorials (does two instead)
    for(int i = n; i > m; i--)
    {
        result *= i;
    }

    //this ought to always be an int but who knows
    return (int)(result / j);




}




int main()
{
    printf("Factorial tests\n");

    for(int i = 0; i < 11; i++)
    {
        printf("%2i : %i\n", i, fact(i));
    }

    printf("\n");

    int n = 8;

    printf("n choose m tests with n = %i\n", n);

    for(int i = 1; i <= n; i++)
    {
        printf("%i choose %2i : %i\n", n, i, choose(n, i));
    }

    return 0;
}
