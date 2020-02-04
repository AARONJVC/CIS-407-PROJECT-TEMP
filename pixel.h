#ifndef PIXEL_H
#define PIXEL_H


class pixel
{
    public:
        pixel();

        void sR(char);
        void sG(char);
        void sB(char);

        char gR();
        char gG();
        char gB();


    private:

        char R;
        char G;
        char B;
        unsigned index;
};

#endif // PIXEL_H
