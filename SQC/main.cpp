#include <iostream>
#include "../pixel class/pixel.h"
#include "../bitmap class/bitmap.h"

using namespace std;

//testing pixel print
void pixel_print_test()
{
    pixel A_pixel = pixel('A','A','A');
    pixel ABC_pixel = pixel('A','B','C');
    pixel ZZZ_pixel = pixel('Z','Z','Z');
    pixel numbers_pixel = pixel('1','2','3');
    pixel test_pixel = pixel(49, 50, 51);

    printf("\n");

    A_pixel.print_chars();
    printf("\n");
    A_pixel.print_hex();

    printf("\n\n");

    ABC_pixel.print_chars();
    printf("\n");
    ABC_pixel.print_hex();

    printf("\n\n");

    ZZZ_pixel.print_chars();
    printf("\n");
    ZZZ_pixel.print_hex();

    printf("\n\n");

    numbers_pixel.print_chars();
    printf("\n");
    numbers_pixel.print_hex();

    printf("\n\n");

    test_pixel.print_chars();
    printf("\n");
    test_pixel.print_hex();

    printf("\n");
}





int main()
{
    cout << "Hello world!" << endl;

    pixel_print_test();

    return 0;
}
