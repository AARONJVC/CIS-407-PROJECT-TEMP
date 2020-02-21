#include "bitmap.h"
//#include "malloc.h"
#include <stdio.h>
#include <stdexcept>
#include "string"
#include <fstream>
#include <iostream>

using namespace std;

#define HEADER_LENGTH 54

bitmap::bitmap(unsigned int h, unsigned int w, char e)
{
    this->pixel_arr = nullptr;

    this->color_arr = nullptr;

    numcolors = 0;

    encoding = e;

    filesize = 0;

    headeroffset = 54;

    importantcolors = 0;

    bitsperpixel = 0;

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

    unsigned char test[HEADER_LENGTH];

    for(int i = 0; i < HEADER_LENGTH; i++)
    {
        read_bmp >> noskipws >> hex >> test[i];
    }

    string file_title = "";

    file_title.append(1, static_cast<char>(test[0]));

    file_title.append(1, static_cast<char>(test[1]));

    cout << endl << file_title << endl;

    if(file_title == "BM")
    {
        cout << endl << "Confirmed BMP file" << endl;
    }

    //BMP encoding stores the file size in little endian format
    unsigned int file_size = test[2] | (test[3] << 8) | (test[4] << 16) | (test[5] << 24);

    unsigned int file_offset = test[10] | (test[11] << 8) | (test[12] << 16) | (test[13] << 24);

    int file_width = test[18] | (test[19] << 8) | (test[20] << 16) | (test[21] << 24);

    int file_height = test[22] | (test[23] << 8) | (test[24] << 16) | (test[25] << 24);

    unsigned int bpp = test[28] | (test[29] << 8);

    unsigned int total_colors = test[46] | (test[47] << 8) | (test[48] << 16) | (test[49] << 24);

    unsigned int important_colors = test[50] | (test[51] << 8) | (test[52] << 16) | (test[53] << 24);

    cout << endl << "Bytes: " << file_size << endl;
    cout << endl << "Header bytes: " << file_offset << endl;
    cout << endl << "Pixel width: " << file_width << endl;
    cout << endl << "Pixel height: " << file_height << endl;
    cout << endl << "Encoding: " << bpp << "b" << endl;
    cout << endl << "Palette colors: " << total_colors << endl;

    bool read_more = true;

    if(file_offset == HEADER_LENGTH)
    {
        cout << endl << "File is not palletized" << endl;
    }
    else if(file_offset >= HEADER_LENGTH)
    {
        cout << endl << "File is palletized" << endl;
    }
    else
    {
        cout << endl << "File error" << endl;

        read_more = false;
    }

    for(int j = 0; j < HEADER_LENGTH; j++)
    {
        if((j % 16) == 0)
        {
            printf("\n");
        }

        printf("%02X ", test[j]);
    }

    printf("\n\n");

    if(read_more)
    {


        unsigned int bytes_per_pixel = (unsigned int)(bpp / 8);

        //bmp pads each scan line to a multiple of 4 bytes, this determines how many bytes it will pad given the image width
        int scan_pad_amount = 4 - ((bytes_per_pixel * file_width) % 4);

        int byte_width = bytes_per_pixel * file_width;

        //each scan line will be this long
        int padded_byte_width = byte_width + scan_pad_amount;

        unsigned char ** pixel_channels = new unsigned char * [file_height];

        for(int i = 0; i < file_height; i++)
        {
            pixel_channels[i] = new unsigned char[padded_byte_width];
        }

        //unsigned int num_pixel_chars = padded_width * file_height;

        //bmp scanlines start in the lower left corner and traverse left to right, upward
        //I want them to start in upper left corner for readability
        for(int i = file_height - 1; i >= 0; i--)
        {
            for(int j = 0; j < padded_byte_width; j++)
            {
                read_bmp >> noskipws >> hex >> pixel_channels[i][j];
            }
        }

        for(int i = 0; i < file_height; i++)
        {
            for(int j = 0; j < padded_byte_width; j++)
            {
                printf("%02X ", pixel_channels[i][j]);
            }

            printf("\n");
        }

        printf("\n\n");

        for(int i = 0; i < file_height; i++)
        {
            for(int j = 0; j < byte_width; j++)
            {
                printf("%02X ", pixel_channels[i][j]);
            }

            printf("\n");
        }


        //now to convert these chars to pixels...

        pixel_arr = new pixel*[file_height];

        for(int i = 0; i < file_height; i++)
        {
            pixel_arr[i] = new pixel[file_width];
        }


        for(int i = 0; i < file_height; i++)
        {
            //this should skip the padded bytes on the ends
            //also traverse in multiples of three (only supported bytes-per-pixel amount so far...)
            for(int j = 0; j < file_width; j++)
            {
                int k = j * 3;

                pixel_arr[i][j] = pixel((pixel_channels[i][k + 2]), (pixel_channels[i][k + 1]), (pixel_channels[i][k]));

                //printf("\n%02X %02X %02X\n", (pixel_channels[i][k + 2]), (pixel_channels[i][k + 1]), (pixel_channels[i][k]));
            }
        }

        for(int i = 0; i < file_height; i++)
        {
            delete[] pixel_channels[i];
        }

        delete[] pixel_channels;



    }

    read_bmp.close();

    bitsperpixel = bpp;
    filesize = file_size;
    headeroffset = file_offset;
    width = file_width;
    height = file_height;
    importantcolors = important_colors;

    return true;
}

bool bitmap::write_file(string new_name)
{
    fstream write_bmp;

    write_bmp.open(new_name, fstream::app);

    write_bmp << hex << 'B' << 'M' << endl;

    //write total bytes as little-endian unsigned int

    //









    unsigned char test[HEADER_LENGTH];

    test[0] = 'B';

    test[1] = 'M';

    //convert filesize back into little-endian chars and store in the output array
    unsigned int file_size = filesize;

    for(int i = 2; i < 6; i++)
    {
        test[i] = file_size;

        file_size >>= 8;
    }

    //fill the reserved space with default value = 0
    for(int i = 6; i < 10; i++)
    {
        test[i] = 0x00;
    }

    unsigned int file_offset = headeroffset;

    for(int i = 10; i < 14; i++)
    {
        test[i] = file_offset;

        file_offset >>= 8;
    }

    //image info header size, which is always 40
//    unsigned int header_size = 40;
//
//    for(int i = 14; i < 18; i++)
//    {
//        test[i] = header_size;
//
//        header_size >>= 8;
//    }

//    int file_width = width;
//
//    for(int i = 18; i < 22; i++)
//    {
//        test[i] = file_width;
//
//        file_width >>= 8;
//    }

    unint_to_LE_chars(40, 14, 18, test);

    unint_to_LE_chars(width, 18, 22, test);

    int file_height = test[22] | (test[23] << 8) | (test[24] << 16) | (test[25] << 24);

    unsigned int bpp = test[28] | (test[29] << 8);

    unsigned int total_colors = test[46] | (test[47] << 8) | (test[48] << 16) | (test[49] << 24);

    unsigned int important_colors = test[50] | (test[51] << 8) | (test[52] << 16) | (test[53] << 24);




    for(int i = 0; i < HEADER_LENGTH; i++)
    {
        read_bmp >> noskipws >> hex >> test[i];
    }

    cout << endl << "Bytes: " << file_size << endl;
    cout << endl << "Header bytes: " << file_offset << endl;
    cout << endl << "Pixel width: " << file_width << endl;
    cout << endl << "Pixel height: " << file_height << endl;
    cout << endl << "Encoding: " << bpp << "b" << endl;
    cout << endl << "Palette colors: " << total_colors << endl;

    bool read_more = true;

    if(file_offset == HEADER_LENGTH)
    {
        cout << endl << "File is not palletized" << endl;
    }
    else if(file_offset >= HEADER_LENGTH)
    {
        cout << endl << "File is palletized" << endl;
    }
    else
    {
        cout << endl << "File error" << endl;

        read_more = false;
    }

    for(int j = 0; j < HEADER_LENGTH; j++)
    {
        if((j % 16) == 0)
        {
            printf("\n");
        }

        printf("%02X ", test[j]);
    }

    printf("\n\n");

    if(read_more)
    {


        unsigned int bytes_per_pixel = (unsigned int)(bpp / 8);

        //bmp pads each scan line to a multiple of 4 bytes, this determines how many bytes it will pad given the image width
        int scan_pad_amount = 4 - ((bytes_per_pixel * file_width) % 4);

        int byte_width = bytes_per_pixel * file_width;

        //each scan line will be this long
        int padded_byte_width = byte_width + scan_pad_amount;

        unsigned char ** pixel_channels = new unsigned char * [file_height];

        for(int i = 0; i < file_height; i++)
        {
            pixel_channels[i] = new unsigned char[padded_byte_width];
        }

        //unsigned int num_pixel_chars = padded_width * file_height;

        //bmp scanlines start in the lower left corner and traverse left to right, upward
        //I want them to start in upper left corner for readability
        for(int i = file_height - 1; i >= 0; i--)
        {
            for(int j = 0; j < padded_byte_width; j++)
            {
                read_bmp >> noskipws >> hex >> pixel_channels[i][j];
            }
        }

        for(int i = 0; i < file_height; i++)
        {
            for(int j = 0; j < padded_byte_width; j++)
            {
                printf("%02X ", pixel_channels[i][j]);
            }

            printf("\n");
        }

        printf("\n\n");

        for(int i = 0; i < file_height; i++)
        {
            for(int j = 0; j < byte_width; j++)
            {
                printf("%02X ", pixel_channels[i][j]);
            }

            printf("\n");
        }


        //now to convert these chars to pixels...

        pixel_arr = new pixel*[file_height];

        for(int i = 0; i < file_height; i++)
        {
            pixel_arr[i] = new pixel[file_width];
        }


        for(int i = 0; i < file_height; i++)
        {
            //this should skip the padded bytes on the ends
            //also traverse in multiples of three (only supported bytes-per-pixel amount so far...)
            for(int j = 0; j < file_width; j++)
            {
                int k = j * 3;

                pixel_arr[i][j] = pixel((pixel_channels[i][k + 2]), (pixel_channels[i][k + 1]), (pixel_channels[i][k]));

                //printf("\n%02X %02X %02X\n", (pixel_channels[i][k + 2]), (pixel_channels[i][k + 1]), (pixel_channels[i][k]));
            }
        }

        for(int i = 0; i < file_height; i++)
        {
            delete[] pixel_channels[i];
        }

        delete[] pixel_channels;



    }

    write_bmp.close();

    return true;
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
            pixel_arr[i][j].print_hex();

            printf(" ");
        }

        printf("\n\n");
    }
}

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

//helps me convert unsigned ints into little-endian chars within an array
void unint_to_LE_chars(unsigned int input, int start, int past_end, *unsigned char arr)
{
    for(int i = start; i < past_end; i++)
    {
        arr[i] = input;

        input >>= 8;
    }
}
