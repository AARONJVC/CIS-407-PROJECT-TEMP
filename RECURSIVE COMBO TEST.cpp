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

int main()
{
    printf("Factorial tests\n");

    for(int i = 0; i < 11; i++)
    {
        printf("%2i : %i\n", i, fact(i));
    }

    return 0;
}
