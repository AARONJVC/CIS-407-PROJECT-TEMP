#include "bitmap.h"
#include "malloc.h"
#include <stdio.h>

bitmap::bitmap(unsigned int h, unsigned int w, char e)
{
    this->pixel_arr = nullptr;

    this->colors_arr = nullptr;

    numcolors = 0;

    encoding = e;

    height = h;

    width = w;

    if(height == 0 || width == 0)
    {
        printf("\n\nINVALID INPUT\n\n");
    }
    else
    {
        //malloc_pixels(height, width);
    }

    return;
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


        /*
        temp = nullptr;


        if(temp != nullptr)
        {
            printf("\n\nFREE ERROR IN A WIDTH ARRAY\n\n");
        }
        */
    }

    free(this->pixel_arr);


    /*
    if(this->pixel_arr != nullptr)
    {
        printf("\n\nFREE ERROR IN A HEIGHT ARRAY\n\n");
    }
    */
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
    //free_pixels();
}
