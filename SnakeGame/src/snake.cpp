#include "snake.h"

snake::snake(COORD pos,int vel)
{
    len = 1;
    this->pos = pos;
    this->vel = vel;
    direction = 'n';
}
void snake::change_dir(char dir){
    direction = dir;
}
void snake::move_snake(){
    switch(direction)
    {
        case 'w':pos.Y-=vel;break;
        case 's':pos.Y+=vel;break;
        case 'd':pos.X+=vel;break;
        case 'a':pos.X-=vel;break;

    }
    body.push_back(pos);
    if(body.size()>len)
        body.erase(body.begin());
}

COORD snake::get_pos(){
    return pos;
}
bool snake::is_eaten(COORD food_pos){
    return (pos.X==food_pos.X and pos.Y==food_pos.Y);
}
void snake::grow(){
    len++;
}
int snake::get_len(){
    return len;
}

vector<COORD> snake::get_body(){
    return body;
}
