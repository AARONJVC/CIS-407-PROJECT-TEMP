#ifndef CHAR_DATA_H
#define CHAR_DATA_H


class char_data
{
    public:
        char_data();

        char getC();
        int getI();

        void setC(char);
        void setI(int);

        ~char_data();

    private:

        char cdata;

        int index;
};

#endif // CHAR_DATA_H
