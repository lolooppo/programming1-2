#include<bits/stdc++.h>
using namespace std;

class Client;
class BankAccount{
protected:
    static int A;
    double balance;
    string account_id,type;
    Client *owner;
public:
    BankAccount(){
        balance=0;
        type="Basic";
        account_id="FCAI-"+to_string(++A);
        }
    BankAccount(double balance):balance(balance){
        type="Basic";
        account_id="FCAI-"+to_string(++A);
    }

    //setters & getters
    void setBalance(double balance){this->balance=balance;}
    string getAccount_id(){return account_id;}
    double getBalance(){return balance;}
    string getType(){return type;}
    //withdrawing and depositting
    virtual bool withdraw(double target){
        if(balance-target>=0){
            balance-=target;
            return true;}
        return false;
    }
    virtual bool deposit(double target){
        balance+=target;
        return true;
    }
    void setOwner(Client &c);/*{
        owner=&c;
    }*/
    Client* getOwner();
};
int BankAccount::A=0;
class SavingsBankAccount:public BankAccount{
   private:
        double minimumBalance=1000;
    public:
    SavingsBankAccount(double Balance,double minimumBalance):BankAccount(Balance),minimumBalance(minimumBalance){
        type="Saving";
        if(minimumBalance>balance)
            {balance=minimumBalance;
             this->minimumBalance=minimumBalance;
            }
    }
    //setters & getters
    void set_minimumBalance(double minimumBalance){this->minimumBalance=minimumBalance;}
    double get_minimumBalance(){return minimumBalance;}
    bool withdraw(double target){
    if(balance-target>=minimumBalance){
        balance-=target;
        return true;}
    return false;
    }
    bool deposit(double target){
    if(target>=100){
        balance+=target;
        return true;}
    return false;
    }
};
class Client{
private:
    string name,address,phoneNum;
    BankAccount *bankAcc;
public:
    void setbankAcc(BankAccount &ba){
        bankAcc=&ba;
    }
    Client(string name,string address,string phoneNum){
        this->name=name;
        this->address=address;
        this->phoneNum=phoneNum;
    }
    string getName(){return name;}
    string getAddress(){return address;}
    string getPhonenum(){return phoneNum;}

};
void BankAccount::setOwner(Client &c){
        owner=&c;
    }
Client* BankAccount::getOwner(){
        return owner;
}
class BankingApplication{
private:
    vector<BankAccount*>v1;
    vector<Client*>v2;
public:
    ~BankingApplication(){
        for(auto i:v1)
            delete i;

        for(auto i:v2)
            delete i;
    }
    int choice;
    void menu(){
    cout<<"Welcome to FCAI Banking Application\n";
    cout<<"1. Create a New Account\n";
    cout<<"2. List Clients and Accounts\n";
    cout<<"3. Withdraw Money\n";
    cout<<"4. Deposit Money\n";
    cout<<"Please Enter Choice =========> ";
    cin>>choice;
    }
    void run(){
    if(choice==1){
        string Name,Address,Phone,Type;
        double Balance,minb;
        cin.ignore();
        cout<<"Please Enter Client Name =========> ";getline(cin,Name);
        cout<<"Please Enter Client Address =======> ";getline(cin,Address);
        cout<<"Please Enter Client Phone =======> ";getline(cin,Phone);
        cout<<"What Type of Account Do You Like? (1) Basic (2) Saving – Type 1 or 2 =========> ";
            cin>>Type;
        cout<<"Please Enter the Starting Balance =========> ";
            cin>>Balance;
            Client c(Name,Address,Phone);
        if(Type=="1"){
            BankAccount b=BankAccount(Balance);
            v1.push_back(new BankAccount(b));
            cout<<"An account was created with ID "<<b.getAccount_id()<<" and Starting Balance"<<b.getBalance()<<" L.E.\n";
        }
        else if(Type=="2"){
                cout<<"Enter the minimum balance =========> ";
                cin>>minb;
                SavingsBankAccount s(Balance,minb);
                cout<<"An account was created with ID "<<s.getAccount_id()<<" and Starting Balance"<<s.getBalance()<<" L.E.\n";
                v1.push_back(new SavingsBankAccount (s));
        }
        v2.push_back(new Client(c));
        v2[v2.size()-1]->setbankAcc(*v1[v1.size()-1]);
        (v1[v1.size()-1])->setOwner(*v2[v2.size()-1]);

    }
    else if(choice==2){
        for(int i=0;i<v1.size();i++){
            cout<<"name: "<<v1[i]->getOwner()->getName()<<"\n";
            cout<<"address: "<<v1[i]->getOwner()->getAddress()<<"\n";
            cout<<"Phone Num: "<<v1[i]->getOwner()->getPhonenum()<<"\n";
            cout<<"ID: "<<v1[i]->getAccount_id()<<"\n";
            cout<<"Balance: "<<v1[i]->getBalance()<<"\n";
            cout<<"Type: "<<v1[i]->getType()<<"\n";
        }
    }
    else if(choice==3){
        string id;
        double amount;
        bool valid;
        cout<<"Enter your account id: =========> ";
        cin>>id;
        for(int i=0;i<v1.size();i++){
            if(id==v1[i]->getAccount_id()){
                cout<<"Balance: "<<v1[i]->getBalance()<<"\n";
                cout<<"Type: "<<v1[i]->getType()<<"\n";
                while(true){
                    cout<<"Enter the amount : =========> ";
                    cin>>amount;
                    valid=v1[i]->withdraw(amount);
                    if(valid){
                        cout<<"Done..your new balance is now:   "<<v1[i]->getBalance()<<"\n";
                        break;
                        }
                    else cout<<"Oops,There are not enough money...please try again\n";

                }
            break;
            }
        }

    }
    else if(choice==4){
        string id;
        double amount;
        bool valid;
        cout<<"Enter your account id: =========> ";
        cin>>id;
        for(int i=0;i<v1.size();i++){
            if(id==v1[i]->getAccount_id()){
                cout<<"Balance: "<<v1[i]->getBalance()<<"\n";
                cout<<"Type: "<<v1[i]->getType()<<"\n";
                while(true){
                    cout<<"Enter the amount : =========> ";
                    cin>>amount;
                    valid=v1[i]->deposit(amount);
                    if(valid){
                        cout<<"Done..your new balance is now:   "<<v1[i]->getBalance()<<"\n";
                        break;
                        }
                    else cout<<"Oops,you can not deposit under 100...please try again\n";

                }
            break;
            }
        }

    }
}
};
int main(){
    BankingApplication Alaa;
    bool cn=true;
    while(cn){
        Alaa.menu();
        Alaa.run();
        cout<<"\nwanna continue? one or zero:  ";
        cin>>cn;
    }

}
