#include "BigDecimalInt.h"


string leadingZero(string s){
    int i=0;
    while(s[i]=='0')i++;
    if(i==s.size())s="0";
    else s.erase(0,i);
    return s;
}

void fun(string num,int k){
    if((num[k]-48)+('1'-48)>9){
        num[k]='0';
        fun(num,k-1);
    }
}

int biggerOne(string n1,string n2){
    for(int i=0;i<n1.size();i++){
        if(n1[i]>n2[i])return 1;
        else if(n1[i]<n2[i])return 2;
    }
}

void fun2(string &s,int k){
    if(s[k]=='0'){
        s[k]='9';
        fun2(s,k-1);
    }
    else{
        s[k]=(s[k]-48-1)+48;
    }
}

void sameSize(int &sz1,int &sz2,string &n1, string &n2){
    if(sz1<sz2)
        {
        reverse(n1.begin(),n1.end());
        for(int i=0;i<sz2-sz1;i++)
            n1+='0';
        reverse(n1.begin(),n1.end());
    }
    else if(sz2<sz1){
        reverse(n2.begin(),n2.end());
        for(int i=0;i<sz1-sz2;i++)
            n2+='0';
        reverse(n2.begin(),n2.end());
    }
    sz1=n1.size(),sz2=n2.size();
}

string Sub(string &n1,string &n2){
    int sz1=n1.size(),sz2=n2.size();
    string n3="";
    sameSize(sz1,sz2,n1,n2);
    int sz=n1.size();
    int trgt=biggerOne(n1,n2);

    if(trgt==2){
        swap(n1,n2);
    }

    for(int i=sz-1;i>=0;i--){
        int res=(n1[i]-48)-(n2[i]-48);
        if(res<0){
            fun2(n1,i-1);
            res=(n1[i]-48+10)-(n2[i]-48);
        }
        n3+=char(res+48);
    }

    reverse(n3.begin(),n3.end());
    n3=leadingZero(n3);

    if(trgt==2){
        reverse(n3.begin(),n3.end());
        n3+="-";
        reverse(n3.begin(),n3.end());
    }
    return n3;
}

string Add(string& n1,string& n2){
    string num3="";
    bool is=false;

    int sz1=n1.size(),sz2=n2.size();

    sameSize(sz1,sz2,n1,n2);

    for(int i=sz1-1;i>=0;i--){
        int res=(n1[i]-48)+(n2[i]-48);
        if(res>9){
            res-=10;
            if(i==0){is=true;}
            else {
                fun(n1,i-1);
                n1[i-1]=((n1[i-1]-48+1)+48);
            }
        }
        num3+=char(res+48);
    }

    if(is){num3+='1';is=false;}
    reverse(num3.begin(),num3.end());
    num3=leadingZero(num3);
    return num3;
}

bool reg(string n){
    regex ex("[+-]?[0-9]+");
    return regex_match(n,ex);
}

string BigDecimalInt::getnum(){
    return num;
}

BigDecimalInt::BigDecimalInt(string anotherDec):num(anotherDec)
{
    if(!reg(anotherDec)){
        cout<<"Not valid number!";
        exit(0);
    }
}

void BigDecimalInt::setnum(string anotherDec){
    num=anotherDec;
}

BigDecimalInt BigDecimalInt::operator=(BigDecimalInt anotherDec){
    num=anotherDec.num;
    return *this;
}

string remove_zeros(string number){
    while (true){
        if(number[0]=='-' && number[1]=='0'){
            number.erase(1,1);
        }
        else if(number[0]=='0'){
            number.erase(0,1);
        }
        else{
            break;
        }
    }
    return number;
}

bool BigDecimalInt::operator>(BigDecimalInt anotherDec){
    if(num[0]=='+'){
        num.erase(0,1);
    }
    if(anotherDec.num[0]=='+'){
        anotherDec.num.erase(0,1);
    }
    num=remove_zeros(num);
    anotherDec.num=remove_zeros(anotherDec.num);  
    if((num[0]=='-') && (anotherDec.num[0]=='-')){
        for (int i = 1; i < max(anotherDec.num.length(),num.length()); i++){
            string n1="",n2="";
            n1+=num[i];
            n2+=anotherDec.num[i];  
            if(num==anotherDec.num){
                return false;
            }
            else if((num.length())>(anotherDec.num.length())){
                return false;
            }
            else if((num.length())<(anotherDec.num.length())){
                return true;
            }
            else if(stoi(n1)>stoi(n2)){ 
                return false;
            }
            else if(stoi(n1)<stoi(n2)){
                return true;
            }
        } 
    }
    else{
        for (int i = 0; i < max(anotherDec.num.length(),num.length()); i++){
            string n1="",n2="";
            n1+=num[i];
            n2+=anotherDec.num[i];
            if(num==anotherDec.num){
                return false;
            }
            else if((num[0]=='-') && (anotherDec.num[0]!='-')){  
                return false;
            }
            else if((num[0]!='-') && (anotherDec.num[0]=='-')){
                return true;
            }
            else if((num.length())>(anotherDec.num.length())){
                return true;
            }
            else if((num.length())<(anotherDec.num.length())){
                return false;
            }
            else if(stoi(n1)>stoi(n2)){
                return true;
            }
            else if(stoi(n1)<stoi(n2)){
                return false;
            }
        } 
    }
}

bool BigDecimalInt::operator==(BigDecimalInt anotherDec){
    if(num[0]=='+'){
        num.erase(0,1);
    }
    if(anotherDec.num[0]=='+'){
        anotherDec.num.erase(0,1);
    }
    num=remove_zeros(num);
    anotherDec.num=remove_zeros(anotherDec.num);  
    if(num==anotherDec.num){  
        return true;
    }
    else{
        return false;
    } 
    return true;
}

int BigDecimalInt::size(){
    if(num[0]=='+' || num[0]=='-'){
        num.erase(0);
    }
    string n=leadingZero(num);
    return n.size();  
}

char BigDecimalInt::sign(){
    if(num[0]=='+' || isdigit(num[0])){
        return '+';
    }
    else{
        return '-';
    }
}

ostream &operator<<(ostream &out, BigDecimalInt b){
    out<<b.num;
    return out;
}

bool BigDecimalInt::operator < (BigDecimalInt anotherDec){

    string n1=num, n2=anotherDec.num; 

    char sign1='+',sign2='+';
    if(n1[0]=='+' or n1[0]=='-'){
        sign1=n1[0];
        n1.erase(0,1);
    }
    if(n2[0]=='+' or n2[0]=='-'){
        sign2=n2[0];
        n2.erase(0,1);
    }

    int sz1=n1.size(), sz2=n2.size();

    if(sign1=='+' and sign2=='-'){
        return false;
    }

    if (sign1=='-' and sign2=='+'){
        return true;
    }

    if(sign1==sign2 and sign1=='+'){
        sameSize(sz1,sz2,n1,n2);
        if(n1==n2){
            return false;
        }

        for(int i=0;i<n1.size();i++){
            if(n1[i]<n2[i]){
                return true;
            }
            if(n1[i]>n2[i]){
                return false;
            }
        }
    }
    else if(sign1==sign2 and sign1=='-'){
        sameSize(sz1,sz2,n1,n2);
        if(n1==n2){
            return false;
        }
        for(int i=0;i<n1.size();i++){
            if(n1[i]>n2[i]){
                return true;
            }
            else if(n1[i]<n2[i]){
                return false;
            }
        }
    }
}

BigDecimalInt BigDecimalInt::operator+(BigDecimalInt anotherDec){

    BigDecimalInt c("");
    string n1=num,n2=anotherDec.num;
    if(n1[0]!='-' and n2[0]!='-'){
        if(n1[0]=='+'){
            n1.erase(0,1);
        }
        if(n2[0]=='+'){
            n2.erase(0,1);
        }
        string num3=Add(n1,n2);
        c.setnum(num3);
    }

    else if(n1[0]!='-' and n2[0]=='-'){
        string n3;
        n2.erase(0,1);
        if(n1[0]=='+'){
            n1.erase(0,1);
        } 
        n3=Sub(n1,n2);
        c.setnum(n3);
    }
    else if(n1[0]=='-' and n2[0]!='-'){
        if(n2[0]=='+'){
            n2.erase(0,1);
        }
        n1.erase(0,1);
        string temp=n1;
        n1=n2;
        n2=temp;
        string n3=Sub(n1,n2);
        c.setnum(n3);
    }
    else if(n1[0]=='-' and n2[0]=='-'){
        n1.erase(0,1);
        n2.erase(0,1);

        string num3=Add(n1,n2);
        reverse(num3.begin(),num3.end());
        num3+='-';
        reverse(num3.begin(),num3.end());
        c.setnum(num3);
    }
    return c;
}

BigDecimalInt BigDecimalInt::operator-(BigDecimalInt anotherDec){
    
    BigDecimalInt c("");
    string n1=num,n2=anotherDec.num;
    if(n1[0]!='-' and n2[0]!='-'){
        if(n1[0]=='+'){
            n1.erase(0,1);
        }
        if(n2[0]=='+'){
            n2.erase(0,1);
        }
        string n3=Sub(n1,n2);
        c.setnum(n3);
    }
    else if(n1[0]!='-' and n2[0]=='-'){
        n2.erase(0,1);
        if(n1[0]=='+'){
            n1.erase(0,1);
        }
        string num3=Add(n1,n2);
        c.setnum(num3);
    }
    else if(n1[0]=='-' and n2[0]!='-'){
        n1.erase(0,1);
        if(n2[0]=='+'){
            n2.erase(0,1);
        }
        string num3;
        num3=Add(n1,n2);
        reverse(num3.begin(),num3.end());
        num3+='-';
        reverse(num3.begin(),num3.end());
        c.setnum(num3);
    }
    else if(n1[0]=='-' and n2[0]=='-'){
        n1.erase(0,1);
        n2.erase(0,1);
        string temp=n1,n3;
        n1=n2; 
        n2=temp;
        n3=Sub(n1,n2);
        c.setnum(n3);
    }
    return c;
}
