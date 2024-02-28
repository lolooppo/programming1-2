#include<bits/stdc++.h>
#include"menu.cpp"
using namespace std;
#define spec_num 10
#define valid 5

int cnt_array[spec_num]={0,0,0,0,0,0,0,0,0,0};

struct Patient{
    string name;
    int state;
    int spec;
};

Patient Arr[spec_num][valid];

void left_shift(int spec){
    int pos=cnt_array[spec];

    pos--;

    for(int i=1;i<=pos;i++){
        Arr[spec][i-1]=Arr[spec][i];
    }

}

void right_shift(int spec){
    int pos=cnt_array[spec];

    for(int i=pos;i>0;i--){
        Arr[spec][i]=Arr[spec][i-1];
    }
}

void Add_patient(){

    string name;
    int stat;
    int spec;


    cout<<"Enter name,specialization and stat==> ";
    cin>>name>>spec>>stat;

    int pos=cnt_array[spec-1];

    if(pos==5)
        {cout<<"Sorry,no empty space\n";return;}

    if(stat==1){
        right_shift(spec-1);
        pos=0;
        }


    Arr[spec-1][pos].name=name;
    Arr[spec-1][pos].state=stat;
    Arr[spec-1][pos].spec=spec;


    cnt_array[spec-1]++;

}

void Get_patient(){
    int spec;

    cout<<"Enter specialization==> ";

    cin>>spec;

    int pos=cnt_array[spec-1];

    if(pos==0){cout<<"No patients at this moment have a rest , Dr >_<\n";return;}

    cout<<Arr[spec-1][0].name<<" please go with the Dr\n";

    left_shift(spec-1);

    cnt_array[spec-1]--;
}

void print_patients(int spec,int cnt){
    for(int i=0;i<cnt;i++){
        cout<<Arr[spec][i].name<<" ";
        if(Arr[spec][i].state==1)cout<<"urgent\n";
        else cout<<"regular\n";
    }
}

void print_spec(){
    for(int i=0;i<spec_num;i++){
        if(cnt_array[i]!=0){
            cout<<"There are "<<cnt_array[i]<<" in specialization "<<i+1<<"\n";
            print_patients(i,cnt_array[i]);
        }
    }
}
int main(){

    Menu menu1,menu2;
    menu1.set_color(11);
    int choice1,choice2;
    choice1 = menu1.Gmenu("Start","Quit");
    while(choice1==1){
        choice2 = menu2.Gmenu("1)Add patient","2)Get patient","3)Print patient","4)Quit");
        if(choice2==1){Add_patient();Sleep(2000);}
        else if(choice2==2){Get_patient();Sleep(7000);}
        else if(choice2==3){print_spec();Sleep(20000);}
        else choice1 = menu1.Gmenu("Start","Quit");

    }
    cout<<"Program finished\n";
    return 0;
}
