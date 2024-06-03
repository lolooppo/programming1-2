#include <bits/stdc++.h>
#include <stdexcept>
#include <stdio.h>



/**************************************************************************************************************************************************
Description : c++ console program to display each process and its machine resources usage but sorted as you desire .        --> (as a task manager)

Purpose : monitor your machine resources and system processes.
***************************************************************************************************************************************************/



using namespace std;


//process class
class process{
public:
    string exec(const char* cmd) {
        char buffer[128];
        string result = "";


        FILE* pipe = popen(cmd, "r");


        if (!pipe)
            throw runtime_error("popen() failed!");

        try {

            while (fgets(buffer, sizeof buffer, pipe) != NULL) {
                result += buffer;

            }

        } catch (...) {

            pclose(pipe);
            throw;

        }

        pclose(pipe);

        return result;
    }

};



//Text to lines splitter function
vector<string> splitter(string& content){
    vector<string> split_content;
    string x="";


    for(int i=0;i<content.size();i++)
        {
            if(content[i]!='\n')
                x+=content[i];

            else{
                split_content.push_back(x);
                x="";
            }

        }

    return split_content;
}




//lines to words splitter function
vector<string> vectorWord(string s, char delimiter)
{

    string sub=s.substr(0,25);
    vector<string> v;
    string temp = "";
    v.push_back(sub);


    for (int i = 25; i < s.length(); i++)
    {
        if (s[i] != delimiter)
            temp += s[i];


        else if(s[i]==delimiter&&s[i+1]==delimiter)
            continue;


        else{
            if(!temp.empty())
                v.push_back(temp);

            temp = "";
        }
    }



    v.push_back(temp);
    return v;
}



//TaskManager class
class TaskManager{
private:
    string image_name,session_name,sessIon_;
    int pid,mem_usage;


public:
    friend bool compare_name(TaskManager a,TaskManager b);
    friend bool compare_pid(TaskManager a,TaskManager b);
    friend bool compare_memuse(TaskManager a,TaskManager b);



    //setters
    void setimageName(string s){image_name=s;}
    void setSessionName(string s){session_name=s;}
    void setPid(int i){pid=i;}
    void setMemusage(int i){mem_usage=i;}
    void setSessIon_(string s){sessIon_=s;}



    //getters
    string getimageName(){return image_name;}
    string getSessionName(){return session_name;}
    int getPid(){return pid;}
    int getMemusage(){return mem_usage;}
    string getSessIon_(){return sessIon_;}
};



//compare functions
bool compare_name(TaskManager a,TaskManager b){return a.image_name<b.image_name;}
bool compare_pid(TaskManager a,TaskManager b){return a.pid<b.pid;}
bool compare_memuse(TaskManager a,TaskManager b){return a.mem_usage<b.mem_usage;}



//objects vector
vector<TaskManager>vOb;

int main()
{
    process P;
    string sentence = P.exec("tasklist");
    vector<string> lines = splitter(sentence);          //lines vector


    for(int i=4;i<lines.size();i++){
        TaskManager T;
        vector<string>V;                //words vector
        V=vectorWord(lines[i],' ');

        //set values int T attributes
        T.setimageName(V[0]);
        T.setPid(stoi(V[1]));
        T.setSessionName(V[2]);
        T.setSessIon_(V[3]);


        //removing (,) for ability to use stoi
        V[4].erase(remove(V[4].begin(), V[4].end(),','), V[4].end());
        T.setMemusage(stoi(V[4]));
        vOb.push_back(T);
    }



    int choice;
    cout<<"Enter your choice\n1) for name\n2) for id\n3) for memory use: \n";cin>>choice;

    if(choice==1)
        sort(vOb.begin(),vOb.end(),compare_name);
    else if(choice==2)
        sort(vOb.begin(),vOb.end(),compare_pid);
    else
        sort(vOb.begin(),vOb.end(),compare_memuse);

    for(auto i:vOb){
        cout<<setw(30)<<left<<i.getimageName()<<setw(10)<<i.getPid()<<setw(20)<<i.getSessionName()<<setw(10)<<i.getSessIon_()<<setw(10)<<i.getMemusage()<<"K"<<endl;
    }
}
