#include "bitmap.h"
//#include "malloc.h"
#include <stdio.h>
#include <stdexcept>
#include "string"
#include <fstream>
#include <iostream>

using namespace std;

bitmap::bitmap(unsigned int h, unsigned int w, char e)
{
    this->pixel_arr = nullptr;

    this->color_arr = nullptr;

    numcolors = 0;

    encoding = e;

    if(h == 0 || w == 0)
    {
        throw 20;
    }
    else
    {
        height = h;

        width = w;
    }

    if(e != TWENTYFOUR_BIT_RGB && e != SIXTEEN_BIT_RGB && e != EIGHT_BIT_PALLETIZED && e != FOUR_BIT_PALLETIZED)
    {
        throw 30;
    }

}

void bitmap::fill_pixels()
{
    this->pixel_arr = new pixel*[height];

    for(unsigned int i = 0; i < height; i++)
    {
        this->pixel_arr[i] = new pixel[width];
    }

    for(unsigned int i = 0; i < height; i++)
    {
        for(unsigned int j = 0; j < width; j++)
        {
            pixel_arr[i][j] = pixel('R', 'G', 'B');
        }
    }
}

bool bitmap::read_file(string filename)
{
    fstream read_bmp(filename, fstream::in);

    int length = 54;

    unsigned char test[length];

    for(int i = 0; i < length; i++)
    {
        read_bmp >> noskipws >> hex >> test[i];
    }

    /*
    while(read_bmp >> noskipws >> hex >> test)
    {
        i++;

        printf("%02X ", test);

        if((i % 16) == 0)
        {
            printf("\n");
        }
    }
    */



    //printf("\nFilestream created\n");

    //read_bmp.open(filename);

    //printf("\nfile opened\n");

    //char test;

    //char[1];

    //read_bmp >> test;

    //printf("\nchar read\n");

    read_bmp.close();

    for(int j = 0; j < length; j++)
    {
        if((j % 16) == 0)
        {
            printf("\n");
        }

        printf("%02X ", test[j]);
    }

    //printf("\nfile closed\n");

    //printf("\n%c\n", test);

    //cout << endl << test << endl;

    //printf("\nchar printed\n");

    return 0;
}

unsigned int bitmap::get_H()
{
    return height;
}

unsigned int bitmap::get_W()
{
    return width;
}

char bitmap::get_E()
{
    return encoding;
}

unsigned int bitmap::get_N()
{
    return numcolors;
}

void bitmap::print()
{
    for(unsigned int i = 0; i < height; i++)
    {
        for(unsigned int j = 0; j < width; j++)
        {
            pixel_arr[i][j].print_chars();

            printf(" ");
        }

        printf("\n\n");
    }
}

/*
//allocates memory for a height * width array of pixels
pixel ** bitmap::malloc_pixels(unsigned int h, unsigned int w)
{
    if(h != 0 && w != 0)
    {
        this->pixel_arr = (pixel**)malloc(sizeof(pixel *) * h);

        if(this->pixel_arr == nullptr)
        {
            printf("\n\nMALLOC ERROR IN A WIDTH ARRAY\n\n");

            return nullptr;
        }

        for(unsigned int i = 0; i < h; i++)
        {
            pixel * temp = (pixel*)malloc(sizeof(pixel) * w);

            this->pixel_arr[i] = temp;

            if(temp == nullptr)
            {
                printf("\n\nMALLOC ERROR IN A WIDTH ARRAY\n\n");
            }
        }

        return this->pixel_arr;
    }
    else
    {
        return nullptr;
    }
}

void bitmap::free_pixels()
{
    for(unsigned int i = 0; i < height; i++)
    {
        pixel * temp = this->pixel_arr[i];

        free(temp);



        temp = nullptr;


        if(temp != nullptr)
        {
            printf("\n\nFREE ERROR IN A WIDTH ARRAY\n\n");
        }

    }

    free(this->pixel_arr);



    if(this->pixel_arr != nullptr)
    {
        printf("\n\nFREE ERROR IN A HEIGHT ARRAY\n\n");
    }

}


pixel * bitmap::malloc_colors()
{
    return nullptr;
}


void bitmap::free_colors()
{

}
*/

bitmap::~bitmap()
{
    if(this->color_arr != nullptr)
    {
        delete[] this->color_arr;
    }

    if(this->pixel_arr != nullptr)
    {
        for(unsigned int i = 0; i < height; i++)
        {
            delete[] this->pixel_arr[i];
        }

        delete[] this->pixel_arr;
    }
}
