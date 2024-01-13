#include<iostream>
#include<cstdlib>
#include<time.h> 
#include<fstream> //for file handling
#include<string>
#include<map> //for dictionary
#include <bits/stdc++.h> 
#include <unistd.h> //for sleep

using namespace std;

void addToFile(int score,string name){
    ofstream file;
    file.open("leaderboard.txt",ios::app);
    string record=name+','+to_string(score)+"\n";
    file<<record;
    file.close();
}

string split_c(string str)
{
    string w = "";
    for (auto x : str) 
    {
        if (x == ',')
        {
            return w;
        }
        else {
            w = w + x;
        }
    }
    return w;
}

string split_p(string str)
{
    bool found=false;
    string w = "";
    for (auto x : str) 
    {
        if (x == ',')
        {
            found=true;
        }
        else {
            if (found)
            w = w + x;
        }
    }
    return w;
}

bool cmp(pair<string, int>& a, pair<string, int>& b) { 
    return a.second > b.second; 
} 

void sort(map<string, int>& M,float pause) 
{ //taken from GeeksforGeeks.org
    // Declare vector of pairs 
    vector<pair<string, int> > A; 
 
    // Copy key-value pair from Map 
    // to vector of pairs 
    for (auto& it : M) { 
        A.push_back(it); 
    } 
 
    // Sort using comparator function 
    sort(A.begin(), A.end(), cmp); 
    //My original code
    int i=1;
    const int len=30; //change this for shortening width
    string stars ((len+13-11)/2,'*'); 
    string underscores(len+14,'_');
    cout<<"\n"<<stars<<"Leaderboard"<<stars<<"\n"<<underscores<<endl;
    string space (len-4,' ');
    cout<<"|    Name"<<space<<"  Score |"<<endl;
    for (auto& it : A) { 
        sleep(pause*2);
        int spaces=len-(it.first.length());
        string blank (spaces,'.');
        cout << "| "<<i<<". "<<it.first <<" "<<blank<<". "<< it.second << "   |"<< endl;
        i++; 
    } 
    string under (len+12,'_');
    cout<<"|"<<under<<"|\n"<<endl;
} 

void getLeaderboard(float pause){
    string myText;
    ifstream file("leaderboard.txt");
    int i=0;
    int j=0;
    string name="";
    string score="";
    while (getline(file, myText)){
        i++;
    }
    map<string,int> lbrd;
    file.clear();
    file.seekg(0);
    while (getline(file,myText)){
        name=split_c(myText);
        score=split_p(myText);
        lbrd[name]=stoi(score);
        j++;
        }
    sort(lbrd,pause);
    //displayLeaderboard(lbrd,i);
    return;
}

void startGame(float pause){
    int score=100;
    srand(time(0));
    string name;
    int a = rand();
    int b=rand();
    int N=100;
    int guess;
    if (b%2==0){
        N=10;
    };
    a=a%N;
    cout<<"Guess a number: ";
    cin>> guess;
    while (guess!=a){
        score=score-5;
        if (guess>a){
            cout<<"The answer is LOWER than "<<guess<<"\n";
        }
        else{
            cout<<"The answer is HIGHER than "<<guess<<"\n";
        }
        cout<<"Guess the number: ";
        cin>>guess;
        }
    sleep(pause*2);
    cout<<"WINNER!!"<<a<<"\n";
    sleep(pause);
    cout<<"Your score is "<<score<<endl;
    sleep(pause);
    cout<<"\nEnter your name to register your score, enter '1' otherwise\n>>";
    cin>>name;
    if (name=="1"){
        return;
    }
    addToFile(score,name);
    getLeaderboard(pause);
}

void endScreen(float pause){
    sleep(pause*2);
    cout<<"\n***********Thank you for playing RaNumGen***********\n"<<
     " _____       _   _                  _____            \n"<<
 "|  __ \\     | \\ | |                / ____|           \n"<<
 "| |__) |__ _|  \\| |_   _ _ __ ___ | |  __  ___ _ __  \n"<<
 "|  _  // _` | . ` | | | | '_ ` _ \\| | |_ |/ _ \\ '_ \\ \n"<<
 "| | \\ \\ (_| | |\\  | |_| | | | | | | |__| |  __/ | | |\n"<<
 "|_|  \\_\\__,_|_| \\_|\\__,_|_| |_| |_|\\_____|\\___|_| |_|\n";
 sleep(pause*2);
 cout<< "\n************Made by Chirag Sehgal************\n";
 sleep(pause*2);
 cout<< "For more projects, visit linktr.ee/Snehgal\n"<<endl;
}

//under contruction
void adminSettings(float pause){
    cout<<"***************Settings****************\n"<<
    "This part is still udner-construction (aka I got tired :'())"<< endl;
    //to add: Changes in number range (def 1-100), changes in pause timer (def 0.5), clearing leaderboard (password req), adding limit to number of tries(def 20) etc
    sleep(pause);
    cout<<" ";
    return;
}

void gameMenu(float pause){
    int option=0;
    while (true){
    sleep(pause);
    cout<<"\n*****************Menu******************\n";
          sleep(pause);
          cout<<
          "0.Exit\n"<<
          "1.Rules\n"<<
          "2.Play Game\n"<<
          "3.View LeaderBoard\n"<<
          "4.Settings\n"
          "\n>> ";
    cin>>option;
    sleep (pause*2);
    cout<<endl;
    switch (option){
    case 0:    
        endScreen(pause);
        return;
    case 1:
        cout<<"*****************Rules******************\n";
        sleep(pause*4);
        cout<<"> The game will randomly generate a number from 1 to 100."<<endl;
        sleep(pause*4);
        cout<<"> The objective is to guess this random number in the minimum number of turns."<<endl;
        sleep(pause*4);
        cout<<"> After each guess, you will get a hint about whether the number is HIGHER or LOWER than your guess."<<endl;
        sleep(pause*4);
        cout<<"> Using these hints, you make another guess and so on until you've guessed the number correctly."<<endl;
        sleep(pause*4);
        cout<<"> Scoring: You start with 100 points, and each turn you take reduces your total by 5 points."<<endl;
        sleep(pause*4);
        cout<<"> The difficulty of the game can be increased by increasing the number range in the Settings."<<endl;
        sleep(pause);
        cout<<"> Enjoy the game!"<<endl;
        break;
    case 2:
        startGame(pause);
        break;
    case 3:
        getLeaderboard(pause);
        break;
    case 4:
        adminSettings(pause);
        break;
    }
    }
}

void startScreen(float pause){
    cout<<"\n**********Welcome to RaNumGen**********\n";
    sleep(1);
    cout<<
    " _____       _   _                  _____            \n"<<
 "|  __ \\     | \\ | |                / ____|           \n"<<
 "| |__) |__ _|  \\| |_   _ _ __ ___ | |  __  ___ _ __  \n"<<
 "|  _  // _` | . ` | | | | '_ ` _ \\| | |_ |/ _ \\ '_ \\ \n"<<
 "| | \\ \\ (_| | |\\  | |_| | | | | | | |__| |  __/ | | |\n"<<
 "|_|  \\_\\__,_|_| \\_|\\__,_|_| |_| |_|\\_____|\\___|_| |_|\n"<<endl;

    sleep (2);
    gameMenu(pause);}

int main(){
    float pause = 0.5;
    startScreen(pause);
    return 0;
    }
