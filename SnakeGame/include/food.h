#ifndef FOOD_H
#define FOOD_H
#include<windows.h>
#include<cstdlib>
#define WIDTH 50
#define HEIGHT 25
class food
{
    private:
        COORD pos;
    public:
        COORD get_pos();
        void gen_food();
};

#endif // FOOD_H
