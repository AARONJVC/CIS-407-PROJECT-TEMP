#include "../pixel class/pixel.h"

#ifndef BITMAP_H
#define BITMAP_H

class bitmap
{
    public:

        //Chars standing in for encoding types:
        //T = 24b RGB
        //S = 16b RGB
        //E = 8b palletized
        //and maybe:
        //F = 4b palletized
        //but I'm definitely not doing black and white photos
        static const char FOUR_BIT_PALLETIZED = 'F';
        static const char EIGHT_BIT_PALLETIZED = 'E';
        static const char SIXTEEN_BIT_RGB = 'S';
        static const char TWENTYFOUR_BIT_RGB = 'T';

        bitmap(unsigned int, unsigned int, char);

        pixel ** pixel_arr;

        pixel * color_arr;

        void fill_pixels();

        unsigned int get_H();
        unsigned int get_W();
        unsigned int get_N();
        char get_E();

        void print();

        ~bitmap();

    private:

        //The width and height of the image
        //shouldn't ever be a reason to modify these once they are initialized in the constructor, so no setters
        unsigned int height;
        unsigned int width;
        //these are only used if the bmp is 8bit or 4bit palletized
        unsigned int numcolors;
        char encoding;

        //private helper functions that are too dangerous to be public

        //pixel ** malloc_pixels(unsigned int, unsigned int);
        //void free_pixels();

        //pixel * malloc_colors();
        //void free_colors();
};

#endif // BITMAP_H
