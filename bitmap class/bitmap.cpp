#include "bitmap.h"

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












pixel ** malloc_pixels()
{

}

void free_pixels()
{

}

pixel * malloc_colors()
{

}

void free_colors()
{

}














bitmap::~bitmap()
{
    //dtor
}
