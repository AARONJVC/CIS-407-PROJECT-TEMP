#include "../pixel class/pixel.h"
#include <stdio.h>

pixel::pixel()
{

}
/*
pixel::pixel(unsigned int r, unsigned int g, unsigned int b)
{
    unsigned char mask = 0xFF;

    R = (unsigned char)(r & mask);
    G = (unsigned char)(r & mask);
    B = (unsigned char)(r & mask);

}
*/
pixel::pixel(unsigned char r, unsigned char g, unsigned char b)
{
    R = r;
    G = g;
    B = b;
}

pixel::pixel(int t)
{

}

void pixel::setR(unsigned char in)
{
    R = in;
}

void pixel::setG(unsigned char in)
{
    G = in;
}

void pixel::setB(unsigned char in)
{
    B = in;
}

unsigned char pixel::getR()
{
    return R;
}

unsigned char pixel::getG()
{
    return G;
}

unsigned char pixel::getB()
{
    return B;
}

void pixel::print_chars()
{
    printf("%c%c%c", this->R, this->G, this->B);
}

void pixel::print_hex()
{
    printf("0x|%2X|%2X|%2X", this->R, this->G, this->B);
}

pixel::~pixel()
{
    //dtor
}


