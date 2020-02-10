#include "bitmap.h"
#include "malloc.h"
#include <stdio.h>

bitmap::bitmap(unsigned int h, unsigned int w, unsigned int e)
{
    //ctor
}

void bitmap::fill_pixels()
{

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
        }
    }
}

//allocates memory for a height * width array of pixels
pixel ** bitmap::malloc_pixels()
{
    this->pixel_arr = (pixel**)malloc(sizeof(pixel *) * height);

    for(unsigned int i = 0; i < height; i++)
    {
        pixel * temp = (pixel*)malloc(sizeof(pixel) * width);

        this->pixel_arr[i] = temp;
    }

    return this->pixel_arr;
}

void bitmap::free_pixels()
{
    for(unsigned int i = 0; i < height; i++)
    {
        pixel * temp = this->pixel_arr[i];

        free(temp);

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

bitmap::~bitmap()
{
    //dtor
}
