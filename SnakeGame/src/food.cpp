#include "food.h"
#define WIDTH 50
#define HEIGHT 25
void food::gen_food(){
    pos.X = (rand()%(WIDTH-2)) + 1 ;
    pos.Y = (rand()%(HEIGHT-2)) + 1 ;
}
COORD food::get_pos(){
    return pos;
}
