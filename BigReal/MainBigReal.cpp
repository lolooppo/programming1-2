#include "BigReal.h"
#include "BigReal.cpp"
#include "BigDecimalIntClass.h"
#include "BigDecimalIntClass.cpp"
int main(){
    BigReal a("123456789012345678901234567890.044"),b("+113456789011345678901134567890.055"),c("-200000000000000000000000000000.01"),d("-000000000001.335"),e("-1.0"),f("00000000.0"),g("-1.0");

    cout<<"a+b = "<<a+b<<endl;
    cout<<"b-a = "<<b-a<<endl;
    cout<<"a+d = "<<a+d<<endl;
    cout<<"c-d = "<<c-d<<endl;
    cout<<"a+c = "<<a+c<<endl;
    cout<<"sign of number a is "<<a.Sign()<<endl;
    cout<<"sign of number b is "<<b.Sign()<<endl;
    cout<<"sign of number c is "<<c.Sign()<<endl;
    cout<<"size of number f is "<<f.size()<<endl;
    if(a>d){
        cout<<"a>d"<<endl;
    }
    if(c<d){
        cout<<"c<d"<<endl;
    }
    if(g==e){
        cout<<"d==e"<<endl;
    }
    return 0;
}