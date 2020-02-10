#include "../pixel class/pixel.h"

#ifndef BITMAP_H
#define BITMAP_H



class bitmap
{
    public:

        bitmap(unsigned int, unsigned int, unsigned int);

        void fill_pixels();

        unsigned int get_H();
        unsigned int get_W();

        char get_E();

        unsigned int get_N()

        void print();

        ~bitmap();

    private:

        pixel ** pixel_arr;

        //The width and height of the image
        //shouldn't ever be a reason to modify these once they are initialized in the constructor, so no setters
        unsigned int height;
        unsigned int width;

        //Chars standing in for encoding types:
        //T = 24b RGB
        //S = 16b RGB
        //E = 8b palletized
        //and maybe:
        //F = 4b palletized
        //but I'm definitely not doing black and white photos

        char encoding;

        //these are only used if the bmp is 8bit palletized

        unsigned int numcolors;

        pixel * colors_arr;

        //private helper functions that are too dangerous to be public

        pixel ** malloc_pixels();
        void free_pixels();

        pixel * malloc_colors();
        void free_colors();




};

#endif // BITMAP_H
