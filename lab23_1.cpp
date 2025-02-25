#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream data(filename);
    string temp;
    int scr1,scr2,scr3;
    char name[100];
    while(getline(data,temp)){
        sscanf(temp.c_str(),"%[^:]: %d %d %d",name,&scr1,&scr2,&scr3);
        names.push_back(name);
        int totalScore = scr1+scr2+scr3;
        scores.push_back(totalScore);
        grades.push_back(score2grade(totalScore));
    }
}

void getCommand(string &command,string &key){
    string text;
    cout << "Please input your command:\n";
    getline(cin,text);
    char c_command[100];
    char c_key[100];
    sscanf(text.c_str(),"%s %[^\n]",c_command,c_key);
    command = c_command; key = c_key;
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    for(unsigned int i=0;i<grades.size();i++){
        if(key==toUpperStr(names[i])) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i]<<'\n';
            cout << names[i] << "'s grade = " << grades[i]<<'\n';
            cout << "---------------------------------\n";
            return ;
        }
    }
    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names,vector<int> &scores,vector<char> &grades,string key){
    bool flag = 0;
    cout << "---------------------------------\n";
    for(unsigned int i=0; i<grades.size();i++){
        if(grades[i]==key[0]){
            cout << names[i] << " (" << scores[i] <<")"<<'\n';
            flag =1;
        }
    } 
    if(flag==0) cout << "Cannot found.\n";
    cout << "---------------------------------\n"; 
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
