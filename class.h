#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

class invoice{
    public:
    long long int number;
    int totalMiliSeconds;
    int totalMinutes = 0;
    int totalPrice;

};


struct dateClass{
    public:
    int day;
    int month;
    int year;
};


class phoneCall{
    private:
    long long int reciver;
    long long int caller;
    time_t epochTime;
    dateClass date;
    int duration;
    

    public:
    void getData(string file, int index);
    void printInfo();
    void epochToDate();

    //copy functions, return caller, duration etc etc..
    int copyCaller();
    int copyDuration();
    int copyEpochTime();
};


void phoneCall::getData(string file, int index){
    int count = 0;
    string line;
    char c;
    int i = 0;
    ifstream myFile;
    myFile.open(file);
    while (count < index){
        getline(myFile, line);
        count++;
    }

    myFile >> caller >> c >> reciver >> c >> epochTime >> c >> duration >> c;

    epochToDate();
    myFile.close();

}

void phoneCall::printInfo(){
    cout << "caller: " << caller << endl;
    cout << "reciver: " << reciver << endl;
    cout << "call duration: " << duration << endl;
    cout << "date: " << date.year << "-" << date.month << "-" << date.day << endl;
    cout << "_____________________________________________________________" << endl;

}

void phoneCall::epochToDate(){
    struct tm localTime;
    localTime = *localtime(&epochTime);


    date.day = localTime.tm_mday;
    date.month = localTime.tm_mon + 1;
    date.year = localTime.tm_year + 1900;
}

int phoneCall::copyCaller(){
    return caller;
}

int phoneCall::copyDuration(){
    return duration;
}

int phoneCall::copyEpochTime(){
    return epochTime;
}

#endif