#ifndef BIGDECIMALINT_H
#define BIGDECIMALINT_H

#include<iostream>
#include<string>
#include<regex>
#include<algorithm>
using namespace std;

string leadingZero(string s);
void fun(string num,int k);
int biggerOne(string n1,string n2);
void fun2(string &s,int k);
void sameSize(int &sz1,int &sz2,string &n1, string &n2);
string Sub(string &n1,string &n2);
string Add(string& n1,string& n2);
bool reg(string n);
string remove_zeros(string number);


class BigDecimalInt{

    private:
        string num;

    public:
        string getnum();
        void setnum(string anotherDec);

        bool operator> (BigDecimalInt anotherDec);
        bool operator< (BigDecimalInt anotherDec);
        bool operator==(BigDecimalInt anotherDec);
        BigDecimalInt operator= (BigDecimalInt anotherDec);
        BigDecimalInt operator+(BigDecimalInt anotherDec);
        BigDecimalInt operator-(BigDecimalInt anotherDec);
        int size();
        char sign();
        friend ostream& operator << (ostream& out, BigDecimalInt b);



        BigDecimalInt(string n);

};

#endif