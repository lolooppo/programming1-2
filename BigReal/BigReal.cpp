#include "BigReal.h"
#include "BigDecimalIntClass.h"

/*-------------destructor----------------*/ 
BigReal::~BigReal()
{

}
/*-------------------End------------------------*/
/*---------------setNumber----------------------*/ 
void BigReal::setNumber(string number){
	num = number;
	if(num[0] == '-'){
		num.erase(0,1);
		sign = "-";
	}else if(num[0] == '+'){
		num.erase(0,1);
		sign = "+";
	}else{
		sign = "+";
	}
}
/*-------------------End------------------------*/

/*---------------- Default constructor------------------*/
BigReal::BigReal(string number){
	setNumber(number);
}
/*-------------------End------------------------*/

/*------------remove_zeros Function-----------------*/ 
string remove_zeros(string number){
    while (true){
        if((number[0]=='-' || number[0]=='+') && number[1]=='0' && number[2]!='.'){  
            number.erase(1,1);
        }
        else if(number[0]=='0' && number[1]!='.'){
            number.erase(0,1);
        }
        else{
            break;
        }
    }
    return number;
}
/*-------------------End------------------------*/

/*-------------------------Start function Add_zeros-----------------------*/ 
string Add_zeros(int difference){
    string zero="";
    while(difference>0){
        zero+="0";
        difference--;
    }
    return zero;
}
/*-------------------End--------------------*/

BigReal::BigReal(BigReal &&other){
	num=other.num;
	other.num="0.0";
	sign=other.sign;
	other.sign="+";
}
BigReal& BigReal:: operator= (BigReal&& other){
	num=other.num;
	other.num="0.0";
	sign=other.sign;
	other.sign="+";
	return *this;
}

/*-------------constructor for double-------------------*/ 
BigReal::BigReal(double realNumber){
	setNumber(to_string(realNumber));
}
/*-------------------End--------------------*/

/*------------Copy constructor--------------*/ 
BigReal::BigReal(const BigReal &other){
    num=other.num;
    sign=other.sign;    
}
/*-------------------End--------------------*/

/*---------------Assignment operator---------*/ 
BigReal BigReal::operator=(BigReal other){
    num=other.num;
    sign=other.sign;
    return *this;    
}
/*-------------------End--------------------*/


BigReal::BigReal(BigDecimalInt bigInteger){
    num=bigInteger.getNumber();
	num+=".0";
}
/*-------------------End--------------------*/


string& BigReal::getter(){
    return num;
}
/*-------------------End--------------------*/

/*-------------------------Start +operator-----------------------*/ 
BigReal BigReal::operator+(BigReal &other){
        string zeros;

        zeros=Add_zeros(other.num.substr(other.num.find(".")+1).length()-num.substr(num.find(".")+1).length());
        BigDecimalInt Num1(sign+remove_zeros(num.substr(0,num.find("."))+num.substr(num.find(".")+1)+zeros));
        
        string Num1WithDot=remove_zeros(num.substr(0,num.find("."))+"."+num.substr(num.find(".")+1)+zeros);

        zeros=Add_zeros(num.substr(num.find(".")+1).length()-other.num.substr(other.num.find(".")+1).length());
        BigDecimalInt Num2(other.sign+remove_zeros(other.num.substr(0,other.num.find("."))+other.num.substr(other.num.find(".")+1)+zeros));
        
        string Num2WithDot=remove_zeros(other.num.substr(0,other.num.find("."))+"."+other.num.substr(other.num.find(".")+1)+zeros);

        BigDecimalInt Num(Num1+Num2);

        int PosOfDot=max(Num1WithDot.find("."),Num2WithDot.find("."));

        string Number;

        Number= Num.getNumber();

        if(Number.length()+1==max(Num1WithDot.length(),Num2WithDot.length())){
            Number.insert(PosOfDot,".");
        }
        else if(Number.length()==max(Num1WithDot.length(),Num2WithDot.length())){
            Number.insert(PosOfDot+1,".");
        }
        else{
            Number.insert(PosOfDot-1,".");
        }
        if(Number[0]=='.'){
            Number="0"+Number;
        }

        Number=remove_zeros(Number);
        BigReal Res(Number);
        if(Num.sign()==0){
            Res.sign="-";
        }
        return Res;
}
/*-------------------------End------------------------*/ 

/*-------------------------Start -operator-----------------------*/ 
BigReal BigReal::operator-(BigReal &other){
    string zeros;

    zeros=Add_zeros(other.num.substr(other.num.find(".")+1).length()-num.substr(num.find(".")+1).length());
    BigDecimalInt Num1(sign+remove_zeros(num.substr(0,num.find("."))+num.substr(num.find(".")+1)+zeros));
    
    string Num1WithDot=remove_zeros(num.substr(0,num.find("."))+"."+num.substr(num.find(".")+1)+zeros);

    zeros=Add_zeros(num.substr(num.find(".")+1).length()-other.num.substr(other.num.find(".")+1).length());
    BigDecimalInt Num2(other.sign+remove_zeros(other.num.substr(0,other.num.find("."))+other.num.substr(other.num.find(".")+1)+zeros));
    
    string Num2WithDot=remove_zeros(other.num.substr(0,other.num.find("."))+"."+other.num.substr(other.num.find(".")+1)+zeros);
    
    BigDecimalInt Num(Num1-Num2);
    
    int PosOfDot=max(Num1WithDot.find("."),Num2WithDot.find("."));

    string Number;

    Number= Num.getNumber();

    if(Number.length()+1==max(Num1WithDot.length(),Num2WithDot.length())){
        Number.insert(PosOfDot,".");
    }
    else if(Number.length()==max(Num1WithDot.length(),Num2WithDot.length())){
        Number.insert(PosOfDot+1,".");
    }
    else{
        Number.insert(PosOfDot-1,".");
    }
    if(Number[0]=='.'){
        Number="0"+Number;
    }
    Number=remove_zeros(Number);
	BigReal Res(Number);
	if(Num.sign()==0){
		Res.sign="-";
	}
	return Res;
}
/*----------------------End--------------------------------*/ 

/*------------operator<----------------*/ 
bool BigReal::operator<(BigReal anotherReal){
	int declen1, declen2, fraclen1, fraclen2;

	string decComp1="", decComp2="", fracComp1="", fracComp2="";
	
	// split the number
	string decPart1, decPart2;
	string fracPart1, fracPart2;
	
	// finding (.)
	size_t pos1 = num.find(".");
	size_t pos2 = anotherReal.num.find(".");

	if(pos1 != string::npos){
		decPart1 = num.substr(0, pos1);
		fracPart1 = num.substr(pos1+1);
	}
	else{
		decPart1 = num;
		fracPart1 = "0";
	}
	
	if(pos2 != string::npos){
		decPart2 = anotherReal.num.substr(0, pos2);
		fracPart2 = anotherReal.num.substr(pos2+1);
	}
	else{
		decPart2 = anotherReal.num;
		fracPart2 = "0";
	}	
	declen1 = decPart1.length();
	declen2 = decPart2.length();
	fraclen1 = fracPart1.length();
	fraclen2 = fracPart2.length();
	
	while(declen1 < declen2){
		decComp1+= "0";
		declen1++;
	}
	while(declen2 < declen1){
		decComp2 += "0";
		declen2++;
	}
	decComp1 += decPart1;
	decComp2 += decPart2;
	fracComp1 += fracPart1;
	fracComp2 += fracPart2;
	while(fraclen1 < fraclen2){
		fracComp1+= "0";
		fraclen1++;
	}
	while(fraclen2 < fraclen1){
		fracComp2+= "0";
		fraclen2++;
	}
	
	//checking 
	if(sign== "+" && anotherReal.sign == "-")
		return false;
	else if(sign == "-" && anotherReal.sign == "+")
		return true;
	else if(sign == "+" && anotherReal.sign == "+"){
		if(decComp1 < decComp2)
			return 1;
		else if(decComp1 == decComp2)
			if(fracComp1 < fracComp2)
				return 1;
			else 
				return 0;
		else
			return 0;
		       	
	}else {
		if(decComp1 > decComp2)
			return 1;
		else if(decComp1 == decComp2)
			if(fracComp1 > fracComp2)
				return 1;
			else 
				return 0;
		else
			return 0;
	}
} 
/*-------------------------End------------------------*/ 

/*------------operator>----------------*/ 
bool BigReal::operator>(BigReal anotherReal){
	int declen1, declen2, fraclen1, fraclen2;

	string decComp1="", decComp2="", fracComp1="", fracComp2="";
	
	// split the number
	string decPart1, decPart2;
	string fracPart1, fracPart2;
	
	// finding (.)
	size_t pos1 = num.find(".");
	size_t pos2 = anotherReal.num.find(".");

	if(pos1 != string::npos){
		decPart1 = num.substr(0, pos1);
		fracPart1 = num.substr(pos1+1);
	}
	else{
		decPart1 = num;
		fracPart1 = "0";
	}
	
	if(pos2 != string::npos){
		decPart2 = anotherReal.num.substr(0, pos2);
		fracPart2 = anotherReal.num.substr(pos2+1);
	}
	else{
		decPart2 = anotherReal.num;
		fracPart2 = "0";
	}	
	declen1 = decPart1.length();
	declen2 = decPart2.length();
	fraclen1 = fracPart1.length();
	fraclen2 = fracPart2.length();

	while(declen1 < declen2){
		decComp1+= "0";
		declen1++;
	}
	while(declen2 < declen1){
		decComp2 += "0";
		declen2++;
	}
	decComp1 += decPart1;
	decComp2 += decPart2;
	fracComp1 += fracPart1;
	fracComp2 += fracPart2;
	while(fraclen1 < fraclen2){
		fracComp1+= "0";
		fraclen1++;
	}
	while(fraclen2 < fraclen1){
		fracComp2+= "0";
		fraclen2++;
	}

	//checking 
	if(sign== "+" && anotherReal.sign == "-")
		return true	;
	else if(sign == "-" && anotherReal.sign == "+")
		return false;
	else if(sign == "+" && anotherReal.sign == "+"){
		if(decComp1 > decComp2)
			return 1;
		else if(decComp1 == decComp2)
			if(fracComp1 > fracComp2)
				return 1;
			else 
				return 0;
		else
			return 0;
		       	
	}else {
		if(decComp1 < decComp2)
			return 1;
		else if(decComp1 == decComp2)
			if(fracComp1 < fracComp2)
				return 1;
			else 
				return 0;
		else
			return 0;
	}
} 
/*-------------------------End------------------------*/ 

/*------------operator==----------------*/ 
bool BigReal::operator== (BigReal anotherReal){
   return num > anotherReal.num || num < anotherReal.num ? 0 : 1;
} 
/*------------End----------------*/ 

/*------------size()----------------*/ 
int BigReal::size(){
   return num.length();
} 
/*------------End----------------*/ 

/*------------Sign()----------------*/ 
int BigReal::Sign(){
	return sign=="+" ? 1 : 0;    
} 
/*------------End----------------*/ 

/*--------------operator >>----------------*/ 
ostream& operator << (ostream& out, const BigReal &num){
	if(num.sign == "+")
		out << num.num;
	else{
		out << num.sign << num.num;
	}
	return out;
}
/*------------End----------------*/ 

/*--------------operator >>----------------*/ 
istream& operator >> (istream& in, BigReal &num){
   	in >> num.num;
	if(num.num[0] == '-'){
		num.sign = "-";
		num.num.erase(0,1);
	}else if(num.num[0] == '+'){
		num.sign = "+";
		num.num.erase(0,1);
	}else{
		num.sign = "+";
	}
   return in;
}
/*------------End----------------*/ 
