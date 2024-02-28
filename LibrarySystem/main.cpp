#include <bits/stdc++.h>
using namespace std;
/*#define besmellah ios_base :: sync_with_stdio(0);cin.tie(0);cout.tie(0);*/

int book_cnt{0};
int user_cnt{0};

struct Book{
    int id{0},Availible_quantity{0},Borrowed_quantity{0};
    string bookName{""};
};

struct User{
    string name{""},bookBorrowed{""};
    int id{0};
};

Book Arr[10];
User arr[20];

void Add_book(){

    int id,Availible_quantity;
    string name;

    cout<<"Enter books name ,id and availible quantity: ";
    cin>>name>>id>>Availible_quantity;

    Arr[book_cnt++]=Book{id,Availible_quantity,0,name};

    cout<<"Book has added successfully\n";
}

void Add_user(){

    string name{""},bookBorrowed{""};
    int id{0};

    cout<<"Enter your name and id: ";
    cin>>name>>id;

    arr[user_cnt++]=User{name,"",id};

    cout<<"User has added successfully\n";
}

void Search_book_by_prefix(){
    string prefix;
    cout<<"Enter search key word: ";
    cin>>prefix;
    string temp{""};
    int n=prefix.size();
    bool found{false};

    if(book_cnt==0){
            cout<<"Sorry,there are no books in the library right now\n";
            return;
        }

    for(int i=0;i<book_cnt;i++){
        temp=(Arr[i].bookName).substr(0,n);

        if(temp==prefix){
            cout<<Arr[i].bookName<<"\n";
            found=true;
            continue;
        }

    }

    if(found==false)
        cout<<"Sorry,there are no such book like this\n";
}

void Print_who_borrowed_this_book(){

    string book_name;
    bool isBorrowed{false};

    cout<<"Enter book name: ";
    cin>>book_name;

    for(int i=0;i<user_cnt;i++){
        if(arr[i].bookBorrowed==book_name){
            cout<<arr[i].name<<"\n";
            isBorrowed=true;
            }
    }

    if(isBorrowed==false){
        cout<<"Actually no one has borrowed this book\n";
    }
}

void Print_users(){

    for(int i=0;i<user_cnt;i++)
        cout<<"Name: "<<arr[i].name<<" Id: "<<arr[i].id<<"\n";
}

void Print_books(){

    if(book_cnt==0){
        cout<<"Currently there are no books\n";
        return;
        }

    for(int i=0;i<book_cnt;i++)
        cout<<"Book id: "<<Arr[i].id<<" Book name: "<<Arr[i].bookName<<" Quantity: "<<Arr[i].Availible_quantity<<" Total borrowed: "<<Arr[i].Borrowed_quantity<<"\n";
}

void Borrow_book(){

    string name{""},book_name{""};

    if(book_cnt==0){
            cout<<"Sorry,there are no books in the library right now\n";
            return;
        }

    cout<<"Enter name and the book name:  ";
    cin>>name>>book_name;

    for(int i=0;i<book_cnt;i++){
        if(Arr[i].bookName==book_name && Arr[i].Availible_quantity>0){
                Arr[i].Availible_quantity--;Arr[i].Borrowed_quantity++;
        }
    }

    for(int i=0;i<user_cnt;i++){
        if(arr[i].name==name){
                arr[i].bookBorrowed=book_name;
        }

    }
}

void Return_book(){

    string name{""},book_name{""};

    cout<<"Enter name and the book name:  ";
    cin>>name>>book_name;

    for(int i=0;i<book_cnt;i++){
        if(Arr[i].bookName==book_name ){
                Arr[i].Availible_quantity++;Arr[i].Borrowed_quantity--;
        }
    }

    for(int i=0;i<user_cnt;i++){
        if(arr[i].name==name){
                arr[i].bookBorrowed="";
        }
    }

}

bool sort_by_id(Book &b1,Book &b2){

    return b1.id<b2.id;
}

bool sort_by_name(Book &b1,Book &b2){

    return b1.bookName<b2.bookName;
}

int menu(){
    int choice;

    cout<<"Library menu\n";
    cout<<"1)Add book\n";
    cout<<"2)Add user\n";
    cout<<"3)Search book\n";
    cout<<"4)Print users\n";
    cout<<"5)Print books by id\n";
    cout<<"6)Print books by name\n";
    cout<<"7)Borrow book\n";
    cout<<"8)Return book\n";
    cout<<"9)Print who borrowed this book\n";
    cout<<"10)Exit\n";

    cin>>choice;

    return choice;
}

void library_system(){

    bool run{true};

    while(run){

        int choice=menu();

        if(choice==1)
            Add_book();
        else if(choice==2)
            Add_user();
        else if(choice==3)
            Search_book_by_prefix();
        else if(choice==4)
            Print_users();
        else if(choice==5)
        {
            sort(Arr,Arr+book_cnt,sort_by_id);
            Print_books();
        }
        else if(choice==6)
        {
            sort(Arr,Arr+book_cnt,sort_by_name);
            Print_books();
        }
        else if(choice==7){
            Borrow_book();
        }
        else if(choice==8){
            Return_book();
        }
        else if(choice==9){
            Print_who_borrowed_this_book();
        }
        else{
            run=false;
        }

    }

}

int main()
{
    //besmellah
    library_system();
}
