#include<stdio.h>
#include<cstdlib>

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


//new function to test precise powers of 2 instead of using pow()
//should only be getting positive input so the abs might drop eventually
//ideally, this will just be done in the main function to save on function calls
int raise_2(int x)
{
    unsigned x_pos = abs(x);

    unsigned result = 0x1;

    result = int(result << x_pos);

    return result;
}


//recursive combo counter
//should count the number of possible combos in a pixel encoding given the
//number of channels allowed for modification and the maximum pixel delta allowed

//hope I don't hit a stack overflow on this
int RCC(int channels, int delta)
{
    //when there are no more pixel changes to implement, we are done
    if(delta == 0)
    {
        return 0;
    }

    int combo_count = raise_2(channels) - 1;

    //the number of pixels to implement has decreased because we have used one (covered another level)
    delta--;

    //now count all the level combos that can be placed on top of the level we just implemented
    for(int i = 1; i < channels; i++)
    {
        combo_count += (choose(channels, i) * RCC(i, delta));
    }

    return combo_count;
}

int SCC(int channels, int delta)
{
    delta++;

    channels--;

    int result = delta;

    for(int i = 0; i < channels; i++)
    {

        result *= delta;

    }

    result--;

    return result;
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

    printf("\npower of two tests\n");

    for(int i = 1; i <= 16; i++)
    {
        printf("2^%i : %i\n", i, raise_2(i));
    }

    /*
    printf("\nRCC tests\n");

    int chan = 3;
    int delt = 8;

    printf("RCC(%i, %i) : %i\n", chan, delt, RCC(chan, delt));
    */

    printf("\nSCC tests\n");

    //goal is to keep delta per color channel under 10% of the full range of values the channel can represent

    //option for RGB profiles with 24b or 32b (don't want to mess with transparency?), encode char in one pixel and num in another pixel
    int chan = 3;
    int delt = 6; //6 is well under 1/10th of 256

    printf("SCC(%i, %i) : %i\n", chan, delt, SCC(chan, delt));

    //option for RGB profiles with 16b
    chan = 6;
    delt = 2; //2 is under 1/10th of 32

    printf("SCC(%i, %i) : %i\n", chan, delt, SCC(chan, delt));

    //option for RGB profiles with 8b palletized, encode the char across two pixels
    //encode num across another two pixels
    chan = 2;
    delt = 16; //16 is under 1/10th of 256

    printf("SCC(%i, %i) : %i\n", chan, delt, SCC(chan, delt));

    //option for RGB profiles with 4b palletized, encode the char across eight pixels
    //encode num across another two pixels
    chan = 8;
    delt = 1; //1 is under 1/10th of 16

    printf("SCC(%i, %i) : %i\n", chan, delt, SCC(chan, delt));


    return 0;
}
