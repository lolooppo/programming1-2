// FCAI - OOP - 2022 - Assignment 1
// Program Name: BigDecimalInt
// Program Description: Apply operators on big numbers
// Last Modification Date: 23/10/2022
// First author - ID : Salma Mohammed Mahmoud / 20210161
// Second author - ID : Alaa Ibrahim Mohammed / 20210239
// Third author - ID : Tawfik Mohammed Khalil / 20211024
// Under The Supervision of: Dr. Mohamed El-Ramly

#include "BigDecimalInt.h"
#include "BigDecimalInt.cpp"

int main(){
    BigDecimalInt a("123456789012345678901234567890"),b("+113456789011345678901134567890"),c("-200000000000000000000000000000"),d("-000000000001"),e("-1"),f("00000000");

    cout<<"a+b = "<<a+b<<endl;
    cout<<"b-a = "<<b-a<<endl;
    cout<<"a+d = "<<a+d<<endl;
    cout<<"c-d = "<<c-d<<endl;
    cout<<"a+c = "<<a+c<<endl;
    cout<<"sign of number a is "<<a.sign()<<endl;
    cout<<"sign of number b is "<<b.sign()<<endl;
    cout<<"sign of number c is "<<c.sign()<<endl;
    cout<<"size of number f is "<<f.size()<<endl;
    if(a>d){
        cout<<"a>d"<<endl;
    }
    if(c<d){
        cout<<"c<d"<<endl;
    }
    if(d==e){
        cout<<"d==e"<<endl;
    }
    return 0;
}