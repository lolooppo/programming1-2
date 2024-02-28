#ifndef BIGREAL_H
#define BIGREAL_H

#include<iostream>
#include "BigDecimalIntClass.h"
using namespace std;



class BigReal{
    private:    
        string num;
		string sign;
		void setNumber(string number);
    public:
        BigReal(string n);
        ~BigReal();

        void print();
        string& getter(); // Get num

        BigReal (double realNumber = 0.0); // Default constructor
        BigReal (BigDecimalInt bigInteger); 
        BigReal (BigReal&& other); // Move constructor
        BigReal (const BigReal& other); // Copy constructor
        BigReal operator= (BigReal other); // Assignment operator
        BigReal& operator= (BigReal&& other); // Move assignment
        
        BigReal operator+ (BigReal& other); // Add operator 
        BigReal operator- (BigReal& other); // Sub operator

		bool operator<(BigReal anotherReal);
		bool operator>(BigReal anotherReal);
		bool operator==(BigReal anotherReal);
		int size();
		int Sign();
		friend ostream &operator<<(ostream &out, const BigReal &num);
		friend istream &operator>>(istream &out, BigReal &num);

};

#endif