#include "BigDecimalInt.h"

/*   
    function to remove leading zeros
    get the last leading zero index then remove till it.
*/
string removeleadingZeros(string str){
    
    int idx{0};
    
    //keep moving till the last leading zero idx
    while(str[idx] == '0')
        idx++;

    /*
        check if the string was actually set of zeros , the idx variable reached the end of the string like(0000000)
        , then reassign it to '0'
    */
    if(idx == (int)str.size())
        str="0";

    //otherwise delete zeros till the idx -> (the index of the last leading zero)
    else
        str.erase(0 , idx);
    
    return str;
}


/*
    function to keep updating digits starting from idx digit while addition operation
    example : 999 + 001 ----> 1000
*/
void digitsUpdate1(string num , int idx){
    
    //check if the addition of the current two digits will go greater than 9 , then assign it to 0 then add 1 to the next digit
    if((num[idx] - 48) + ('1' - 48) > 9){
        num[idx] = '0';
        digitsUpdate1(num , idx - 1);
    }
}


/*
    function to keep updating digits starting from idx digit while subtraction operation
    example : 100 - 001 ----> 099
*/
void digitsUpdate2(string& num , int idx){
    
    //check if we can not subtract 1 from the current digit ,then keep borrowing
    if(num[idx] == '0'){
        num[idx] = '9';
        digitsUpdate2(num , idx - 1);
    }
    else{
        num[idx] = num[idx] - 48 - 1 + 48;
    }
}


/*
    function to return 1 if num1 greater than num2 otherwise 2
    by comparing digit by digit from the left to the right
*/
int biggerOne(string num1 , string num2){
    for(int idx = 0;idx < (int)num1.size();idx++){
        if(num1[idx] > num2[idx])
            return 1;
    }
    return 2;
}


/*
    function to make the given two strings (num1 , num2) have the same size by adding leading zeros
*/
void equalize(int& sz1,int& sz2,string& num1, string& num2){
    
    //if num1 size smaller than num2 size ,then reverse num1 the keep adding zeros till be the same size ,then reverse it agian
    if(sz1 < sz2){
        reverse(num1.begin() , num1.end());
        
        for(int idx = 0;idx < sz2-sz1;idx++)
            num1 += '0';
        
        reverse(num1.begin() , num1.end());
    }
        
    //otherwise,do the same as above but for num2
    else if(sz2 < sz1){
        reverse(num2.begin() , num2.end());
        
        for(int idx = 0;idx < sz1-sz2;idx++)
            num2 += '0';
        
        reverse(num2.begin() , num2.end());
    }
    
    //update the sz1 , sz2 variable with the new same size
    sz1 = num1.size() , sz2 = num2.size();
}


/*
    function to subtract two big numbers represented as strings
    first equalize there sizes by adding leading zeros
    then subtract digit by digit and keep updating the rest of digits (like in the borrowing case)
*/
string Sub(string& num1,string& num2){
    int sz1 = num1.size() , sz2 = num2.size();
    string num3="";
    
    equalize(sz1,sz2,n1,n2);
    
    int sz=num1.size();
    int trgt=biggerOne(num1 , num2);

    //but the bigger one in num1 and the smaller one in num2
    if(trgt==2){
        swap(n1,n2);
    }

    for(int idx = sz-1;idx >= 0;idx--){
        int res = (num1[idx] - 48) - (num2[idx] - 48);
        if(res < 0){
            digitsUpdate2(n1,i-1);
            res=(num1[idx] - 48 + 10) - (num2[idx] - 48);
        }
        num3 += char(res + 48);
    }

    reverse(num3.begin() , num3.end());
    
    num3 = removeleadingZeros(num3);

    //if num1 was less than num2 then we have to add neg sign in the result string --> (num3) 
    if(trgt == 2){
        string tmp = "-";
        tmp += num3;
        num3 = tmp;
    }
    
    return num3;
}


/*
    function to add two big numbers represented as strings
    first equalize there sizes by adding leading zeros
    then add digit by digit and keep updating the rest of digits 
*/
string Add(string& num1,string& num2){
    string num3="";
    bool is=false;
    int sz1 = num1.size() , sz2 = num2.size();

    equalize(sz1,sz2,num1,num2);

    for(int idx = sz1 - 1;idx >= 0;idx--){
        int res = (num1[idx] - 48) + (num2[idx] - 48);
        if(res > 9){
            res -= 10;
            if(idx==0)
                is=true;
            else {
                digitsUpdate1(num1 , idx - 1);
                num1[idx - 1] = ((num1[idx - 1] - 48 + 1) + 48);
            }
        }
        num3 += char(res + 48);
    }

    if(is){
        num3+='1';
        is=false;
    }
    
    reverse(num3.begin(),num3.end());
    
    num3 = removeleadingZeros(num3);
    
    return num3;
}


/*

*/
bool reg(string n){
    regex ex("[+-]?[0-9]+");
    return regex_match(n,ex);
}


/*

*/
string BigDecimalInt :: getnum(){
    return num;
}


/*

*/
BigDecimalInt :: BigDecimalInt(string anotherDec):num(anotherDec)
{
    if(!reg(anotherDec)){
        cout<<"Not valid number!";
        exit(0);
    }
}


/*

*/
void BigDecimalInt :: setnum(string anotherDec){
    num=anotherDec;
}


/*

*/
BigDecimalInt BigDecimalInt :: operator=(BigDecimalInt anotherDec){
    num = anotherDec.num;
    return *this;
}



string remove_zeros(string number){
    while (true){
        if(number[0] =='-' && number[1] == '0'){
            number.erase(1,1);
        }
        else if(number[0] == '0'){
            number.erase(0,1);
        }
        else{
            break;
        }
    }
    return number;
}


/*

*/
int BigDecimalInt :: size(){
    if(num[0] == '+' || num[0] == '-'){
        num.erase(0);
    }
    
    string n=removeleadingZeros(num);
    
    return n.size();  
}


/*

*/
char BigDecimalInt :: sign(){
    if(num[0] == '+' || isdigit(num[0])){
        return '+';
    }
    return '-';
}


/*

*/
ostream &operator<<(ostream &out, BigDecimalInt anotherDec){
    out<<anotherDec.num;
    return out;
}
/*

*/
bool BigDecimalInt :: operator>(BigDecimalInt anotherDec){
    if(num[0]=='+'){
        num.erase(0,1);
    }
    
    if(anotherDec.num[0]=='+'){
        anotherDec.num.erase(0,1);
    }
    
    num=removeleadingZeros(num);
    
    anotherDec.num=removeleadingZeros(anotherDec.num);  
    
    if((num[0] == '-') && (anotherDec.num[0] == '-')){
        for (int idx = 1; idx < max(anotherDec.num.length() , num.length()); idx++){
            string num1 = "" , num2 = "";
            
            num1 += num[idx];
            num2 += anotherDec.num[idx];
            
            if(num == anotherDec.num){
                return false;
            }
            else if((num.length()) > (anotherDec.num.length())){
                return false;
            }
            else if((num.length()) < (anotherDec.num.length())){
                return true;
            }
            else if(stoi(num1) > stoi(num2)){ 
                return false;
            }
            else if(stoi(num1) < stoi(num2)){
                return true;
            }
        } 
    }
        
    else{
        for (int idx = 0; idx < max(anotherDec.num.length() , num.length()); idx++){
            string num1 = "", num2 = "";
            
            num1 += num[idx];
            num2 += anotherDec.num[idx];
            
            if(num==anotherDec.num){
                return false;
            }
            else if((num[0]=='-') && (anotherDec.num[0]!='-')){  
                return false;
            }
            else if((num[0]!='-') && (anotherDec.num[0]=='-')){
                return true;
            }
            else if((num.length()) > (anotherDec.num.length())){
                return true;
            }
            else if((num.length()) < (anotherDec.num.length())){
                return false;
            }
            else if(stoi(num1) > stoi(num2)){
                return true;
            }
            else if(stoi(num1) < stoi(num2)){
                return false;
            }
        } 
    }
}


/*

*/
bool BigDecimalInt :: operator==(BigDecimalInt anotherDec){
    if(num[0]=='+'){
        num.erase(0,1);
    }
    if(anotherDec.num[0]=='+'){
        anotherDec.num.erase(0,1);
    }
    
    num=removeleadingZeros(num);
    
    anotherDec.num=removeleadingZeros(anotherDec.num);  
    
    if(num == anotherDec.num){  
        return true;
    }
    else{
        return false;
    } 
    return true;
}


/*

*/
bool BigDecimalInt :: operator < (BigDecimalInt anotherDec){

    string num1 = num, num2 = anotherDec.num; 
    char sign1='+',sign2='+';
    
    if(num1[0] == '+' or num1[0] == '-'){
        sign1 = num1[0];
        num1.erase(0,1);
    }
    if(num2[0] == '+' or num2[0] == '-'){
        sign2 = num2[0];
        num2.erase(0,1);
    }

    int sz1 = num1.size() , sz2=num2.size();

    if(sign1 == '+' and sign2 == '-'){
        return false;
    }

    if (sign1 == '-' and sign2 == '+'){
        return true;
    }

    if(sign1 == sign2 and sign1 == '+'){
        equalize(sz1 , sz2 , num1 , num2);
        
        if(num1 == num2){
            return false;
        }

        for(int idx = 0;i < (int)num1.size();idx++){
            if(num1[idx] < num2[idx]){
                return true;
            }
            if(num1[idx] > num2[idx]){
                return false;
            }
        }
    }
    else if(sign1 == sign2 and sign1 == '-'){
        equalize(sz1 , sz2 , num1 , num2);
        if(num1 == num2){
            return false;
        }
        for(int idx = 0;idx < (int)num1.size();idx++){
            if(num1[idx] > num2[idx]){
                return true;
            }
            else if(num1[idx] < num2[idx]){
                return false;
            }
        }
    }
}


/*

*/
BigDecimalInt BigDecimalInt :: operator+(BigDecimalInt anotherDec){
    BigDecimalInt res("");
    string num1 = num , num2 = anotherDec.num;
    
    if(num1[0] != '-' and num2[0] != '-'){
        if(num1[0] == '+'){
            num1.erase(0,1);
        }
        if(num2[0] == '+'){
            num2.erase(0,1);
        }
        
        string num3=Add(num1 , num2);
        res.setnum(num3);
    }

    else if(num1[0] != '-' and num2[0] == '-'){
        string num3;
        num2.erase(0,1);
        
        if(num1[0] == '+'){
            num1.erase(0,1);
        }
        
        num3=Sub(num1 , num2);
        res.setnum(num3);
    }
    else if(num1[0] == '-' and num2[0] != '-'){
        if(num2[0] == '+'){
            num2.erase(0,1);
        }
        
        num1.erase(0,1);
        string temp = num1;
        num1 = num2;
        num2 = temp;
        string num3=Sub(num1 , num2);
        res.setnum(num3);
    }
    else if(num1[0] == '-' and num2[0] == '-'){
        num1.erase(0,1);
        num2.erase(0,1);

        string num3=Add(num1,num2);
        
        reverse(num3.begin() , num3.end());
        
        num3 += '-';
        
        reverse(num3.begin(),num3.end());
        
        res.setnum(num3);
    }
    return res;
}


/*

*/
BigDecimalInt BigDecimalInt :: operator-(BigDecimalInt anotherDec){
    
    BigDecimalInt res("");
    string num1 = num , num2 = anotherDec.num;
    
    if(num1[0] != '-' and num2[0] != '-'){
        if(num1[0] == '+'){
            num1.erase(0,1);
        }
        if(num2[0]=='+'){
            num2.erase(0,1);
        }
        
        string num3=Sub(num1 , num2);
        
        res.setnum(num3);
    }
    else if(num1[0] != '-' and num2[0] == '-'){
        num2.erase(0,1);
        
        if(num1[0]=='+'){
            num1.erase(0,1);
        }
        
        string num3 = Add(num1 , num2);
        
        res.setnum(num3);
    }
    else if(num1[0] == '-' and num2[0] != '-'){
        num1.erase(0,1);
        if(num2[0]=='+'){
            num2.erase(0,1);
        }
        
        string num3;
        
        num3 = Add(num1 , num2);
        
        reverse(num3.begin(),num3.end());
        
        num3 += '-';
        
        reverse(num3.begin() , num3.end());
        
        res.setnum(num3);
    }
    else if(num1[0] == '-' and num2[0] == '-'){
        num1.erase(0,1);
        num2.erase(0,1);
        string temp = num1 , num3;
        num1 = num2; 
        num2 = temp;
        num3 = Sub(num1 , num2);
        res.setnum(num3);
    }
    return res;
}
