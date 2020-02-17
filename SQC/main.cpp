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

void bitmap_init_test(unsigned int h, unsigned int w, char e)
{
    try
    {
        bitmap test_bmp = bitmap(h, w, e);

        printf("\nExpect height: %i\nActual height: %i\n", h, test_bmp.get_H());

        printf("\nExpect width: %i\nActual width: %i\n", w, test_bmp.get_W());

        printf("\nExpect encoding: %c\nActual encoding: %c\n", e, test_bmp.get_E());

        printf("\nExpect numcolors: %i\nActual numcolors: %i\n", 0, test_bmp.get_N());

        if((test_bmp.get_H() != 0 && test_bmp.get_W() != 0))
        {
            test_bmp.fill_pixels();
        }

        if((test_bmp.get_H() == 0 || test_bmp.get_W() == 0) && test_bmp.pixel_arr == nullptr)
        {
            printf("\nPixel array is null as expected\n");
        }
        else if(test_bmp.get_H() == 0 || test_bmp.get_W() == 0)
        {
            printf("\nPixel array NOT null and H/W are zero\n");
        }

        if(test_bmp.color_arr == nullptr)
        {
            printf("\nColors array is null as expected\n");
        }
        else
        {
            printf("\nColors array is NOT null\n");
        }
    }
    catch(int ex)
    {
        printf("\nException encountered: %i\n", ex);
    }
}

void bmp_init_print_test()
{
    bitmap_init_test(0,0,'Q');

    bitmap_init_test(1,0,'P');

    bitmap_init_test(0,1,'Z');

    bitmap_init_test(1,1,'A');

    bitmap_init_test(10,10,'B');

    bitmap_init_test(1,1,'T');
}

void bmp_printing(unsigned int h, unsigned int w)
{

    try
    {
        bitmap print_test = bitmap(h, w, 'T');

        print_test.fill_pixels();

        print_test.print();
    }
    catch(int ex)
    {
        printf("\nException encountered: %i\n", ex);
    }

}

bool bmp_read_test(string filename)
{
    bitmap read_test = bitmap(2, 2, 'T');

    bool success = read_test.read_file(filename);

    if(success)
    {
        printf("\n\n");

        read_test.print();
    }

    return success;
}

bool bmp_write_test(string new_name)
{
    bitmap write_test = bitmap(2, 2, 'T');

    bool success = write_test.write_file(new_name);

    if(success)
    {
        printf("\nsucceeded\n");
    }

    return success;
}


int main()
{
    //cout << "Hello world!" << endl;

    //pixel_print_test();

    //bmp_init_print_test();

    //bmp_printing(5, 5);

    //bmp_printing(1, 1);

    //bmp_printing(0, 0);

    //bmp_printing(0, 5);

    //bmp_printing(5, 0);

    //bmp_printing(2, 1);

    //bmp_printing(4, 7);

    //bmp_read_test("../TEST BITMAPS/5x5 24b overwrite.bmp");

    bmp_write_test("../TEST OUTPUT/hello.txt");

//    pixel p1 = pixel('A', 'A', 'A');
//
//    pixel p2 = pixel('Z', 'Z', 'Z');
//
//    pixel result = p1 ^ p2;
//
//    result.print_hex();
//
//    result = p2 ^ p1;
//
//    result.print_hex();
//
//    result = p2 ^ p2;
//
//    result.print_hex();
//
//    result = (p2 ^ p2) ^ p1;
//
//    result.print_hex();



    return 0;
}
