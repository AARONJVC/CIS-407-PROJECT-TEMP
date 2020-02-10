#include <iostream>
#include "../pixel class/pixel.h"
#include "../bitmap class/bitmap.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    pixel A_pixel = pixel('A','A','A');
    pixel ABC_pixel = pixel('A','B','C');
    pixel ZZZ_pixel = pixel('Z','Z','Z');
    pixel numbers_pixel = pixel('1','2','3');

    printf("\n");

    A_pixel.print_chars();

    printf("\n");

    ABC_pixel.print_chars();

    printf("\n");

    ZZZ_pixel.print_chars();

    printf("\n");

    numbers_pixel.print_chars();

    printf("\n");

    return 0;
}
