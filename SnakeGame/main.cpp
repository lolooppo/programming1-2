#include<bits/stdc++.h>
#include<ctime>
#include<conio.h>
#include"snake.h"
#include"food.h"
using namespace std;
#define WIDTH 50
#define HEIGHT 25

snake snk({WIDTH/2,HEIGHT/2},1);
food fo;

void drawBoard(){

    COORD snk_pos = snk.get_pos();
    COORD food_pos = fo.get_pos();
    vector<COORD>snake_body = snk.get_body();

    for(int i=0;i<HEIGHT;i++){
        cout<<"\t\t#";
        for(int j = 0;j<WIDTH;j++){
            if(!i or i==HEIGHT-1){
                cout<<"#";
            }
            else if(i==snk_pos.Y and j==snk_pos.X ){
                cout<<'O';
            }
            else if(i==food_pos.Y and j==food_pos.X){
                cout<<"*";
            }
            else{
                bool is_body = false;
                for(int k=0;k<(int)snake_body.size();k++){
                    if(i==snake_body[k].Y and j==snake_body[k].X){
                        cout<<"O";
                        is_body = true;
                        break;
                    }
                }
                if(!is_body)
                    cout<<" ";
            }

        }
        cout<<"#\n";
    }
}
int main(){
    srand(time(NULL));
    fo.gen_food();
    bool game_over;
    while(true){
        drawBoard();
        if(kbhit()){
            switch(getch()){
                case 'w':snk.change_dir('w');break;
                case 'd':snk.change_dir('d');break;
                case 'a':snk.change_dir('a');break;
                case 's':snk.change_dir('s');break;
            }
        }

        snk.move_snake();
        game_over = snk.crash();

        if(game_over){
            system("cls");
            break;
        }

        if(snk.is_eaten(fo.get_pos())){
            fo.gen_food();
            snk.grow();
        }

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});
    }
    cout<<"\n Score:: "<<snk.get_len()-1<<"\n\n";
}
