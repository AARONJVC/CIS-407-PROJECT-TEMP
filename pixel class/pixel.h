#ifndef PIXEL_H
#define PIXEL_H


class pixel
{
    public:
        pixel();
        pixel(unsigned int r, unsigned int g, unsigned int b);
        pixel(unsigned char r, unsigned char g, unsigned char b);
        pixel(int t);


        void setR(unsigned char);
        void setG(unsigned char);
        void setB(unsigned char);

        unsigned char getR();
        unsigned char getG();
        unsigned char getB();


    private:

        unsigned char R;
        unsigned char G;
        unsigned char B;
};

#endif // PIXEL_H
