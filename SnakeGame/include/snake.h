#ifndef SNAKE_H
#define SNAKE_H
#include<windows.h>
#include<vector>
#define WIDTH 50
#define HEIGHT 25
using namespace std;
class snake
{
private:
    int len,vel;
    char direction;
    COORD pos;
    vector<COORD>body;
public:
    snake(COORD pos,int vel);
    void change_dir(char dir);
    void move_snake();
    int get_len();
    COORD get_pos();
    vector<COORD>get_body();
    bool is_eaten(COORD food_pos);
    bool crash(){
        if(pos.X<1 or pos.X==WIDTH)
            return true;
        if(pos.Y<1 or pos.Y==HEIGHT)
            return true;
        return false;
    }
    void grow();
};

#endif // SNAKE_H
