#ifndef BIGDECIMALINT_H
#define BIGDECIMALINT_H

#include<iostream>
#include<string>
#include<regex>
#include<algorithm>
using namespace std;

string removeleadingZeros(string str);
void digitsUpdate1(string num , int idx);
void digitsUpdate2(string& num , int idx);
int biggerOne(string num1 , string num2);
void equalize(int& sz1,int& sz2,string& num1, string& num2);
string Sub(string& num1,string& num2);
string Add(string& num1,string& num2);
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
