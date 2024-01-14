#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h> //log
#include <time.h> 
#include <fstream> //for file handling
#include <string>
#include <map> //for dictionary
#include <bits/stdc++.h> 
#include <unistd.h> //for sleep
#include <cmath>

using namespace std;
float N;
float pause;
float maxTries;

void gameSettings(){
    //first line -> N ; second line-> pause; third line-> max tries;
    string num;
    float arr[3];
    ifstream file ("RaNumGen_settings.txt");
    int i=0;
    while (getline(file, num)){
        arr[i]=stof(num);
        i++;   
    }
    N=arr[0];
    pause=arr[1];
    maxTries=arr[2];

}

void writeSettings(){
    ofstream file;
    file.open("RaNumGen.txt",ios::app);
    string sN=to_string(N)+"\n";
    string spause=to_string(pause)+"\n";
    string smaxTries=to_string(maxTries)+"\n";
    file<<sN;
    file<<spause;
    file<<smaxTries;
    file.close();
}

void addToFile(int score,string name,int level){
    ofstream file;
    file.open("leaderboard.txt",ios::app);
    string record=name+','+to_string((score*7)+level)+"\n";
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
    return (a.second) > (b.second); 
} 

void sort(map<string, int>& M) 
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
    string underscores(len+24,'_');
    cout<<"\n"<<stars<<"Leaderboard"<<stars<<"\n"<<underscores<<endl;
    string space (len-4,' ');
    cout<<"|    Name"<<space<<"  Score |  Level  |"<<endl;
    for (auto& it : A) { 
        sleep(pause*2);
        int spaces=len-(it.first.length());
        string blank (spaces,'.');
        cout << "| "<<i<<". "<<it.first <<" "<<blank<<". "<< it.second/7 << "   |    "<<it.second%7<<"    |"<< endl;
        i++; 
    } 
    string under (len+22,'_');
    cout<<"|"<<under<<"|\n"<<endl;
} 

void getLeaderboard(){
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
    sort(lbrd);
    //displayLeaderboard(lbrd,i);
    return;
}

void startGame(){
    int score=100;
    int decrement=score/maxTries;
    srand(time(0));
    string name;
    int a = rand();
    int b=rand();
    int guess;
    int n;
    int level=log10(N);
    if (b%10>level){
        b=(b-b%10)/10;
    };
    n=pow(10,b%10);
    a=a%n;
    cout<<"Guess a number: ";
    cin>> guess;
    while (guess!=a){
        score=score-decrement;
        if (guess>a){
            cout<<"The answer is LOWER than "<<guess<<"\n";
        }
        else{
            cout<<"The answer is HIGHER than "<<guess<<"\n";
        }
        cout<<"Guess the number: ";
        cin>>guess;
        if (score<0){
            cout<<"\nSorry, you've used up all your turns"<<endl;
            cout<<"\nThe number was "<<a;
            return;
        }
        }
    sleep(pause*2);
    cout<<"WINNER!!"<<"\n";
    sleep(pause);
    score=score*abs(level-maxTries/10);
    cout<<"Your score is "<<score<<endl;
    sleep(pause);
    cout<<"\nEnter your name to register your score, enter '1' otherwise\n>>";
    cin>>name;
    if (name=="1"){
        return;
    }
    addToFile(score,name,level);
    getLeaderboard();
}

void endScreen(){
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

void adminSettings(){
    int option=0;
    float perc=100.0;
    int newLevel=2;
    int newTries=20;
    string password;
    string sure="n";
    while (true){
    cout<<"***************Settings****************\n"<<
    "0. Save and Close"<<endl;
    sleep(pause);
    cout<<"1. Change pause timer (currently "<<pause<<" seconds)"<<endl;
    sleep(pause);
    cout<<"2. Change difficulty (currently at level "<<log10(N)<<" )"<<endl;
    sleep(pause);
    cout<<"3. Change maximum tries allowed (currently a maximum of "<<maxTries<<" tries are allowed)"<<endl;
    sleep(pause);
    cout<<"4. Clear leaderboard"<<endl;
    sleep(pause);
    cout<<"5. Return to default/Cancel"<<endl;
    cout<<">> ";
    cin>>option;
    sleep(pause*2);
    switch (option){
        case 0:
            return;
        case 1:
            cout<<"Enter what percentage of the current pause would you like (0-1000%)\n>>";
            cin>>perc;
            pause=(perc/100.0)*pause;
            break;
        case 2:
            cout<<"Enter the new level of gameplay(0-10)\n>>";
            cin>>newLevel;
            N=pow(10,newLevel);
            break;
        case 3:
            cout<<"Enter new number of maximum tries\n>>";
            cin>>newTries;
            maxTries=newTries;
            break;
        case 4:
            cout<<"Enter the password\n>>";
            cin>>password;
            if (password=="IconfirmIwanttoDELETEleaderboard"){
                cout<<"Are you sure you want to delete the leaderboard? (y/n)\n>>";
                cin>>sure;
                if (sure=="y"){
                    ofstream file;
                    file.open("leaderboard.txt",ios::out);
                    file.close();}
            return;
        case 5:
            N=100;
            pause=0.5;
            maxTries=20;}
    writeSettings();    }}
    //to add: Changes in number range (def 1-100), changes in pause timer (def 0.5), clearing leaderboard (password req), adding limit to number of tries(def 20) etc
}

void gameMenu(){
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
        endScreen();
        return;
    case 1:
        cout<<"*****************Rules******************\n";
        sleep(pause*4);
        cout<<"> The game will randomly generate a number from 1 to "<<N<<"."<<endl;
        sleep(pause*4);
        cout<<"> The objective is to guess this random number in the minimum number of turns. You have a maximum of "<<maxTries<<" turns."<<endl;
        sleep(pause*4);
        cout<<"> After each guess, you will get a hint about whether the number is HIGHER or LOWER than your guess."<<endl;
        sleep(pause*4);
        cout<<"> Using these hints, you make another guess and so on until you've guessed the number correctly."<<endl;
        sleep(pause*4);
        cout<<">Your final score is calculated by [((100-triesTaken)xlevel)-maxTries/5]. Currently, you're at level "<<log10(N)<<endl;
        sleep(pause*4);
        cout<<"> The difficulty of the game can be changed in the Settings."<<endl;
        sleep(pause);
        cout<<"> Enjoy the game!"<<endl;
        break;
    case 2:
        startGame();
        break;
    case 3:
        getLeaderboard();
        break;
    case 4:
        adminSettings();
        break;
    }
    }
}

void startScreen(){
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
    gameMenu();}

int main(){
    gameSettings();
    startScreen();
    return 0;
    }
