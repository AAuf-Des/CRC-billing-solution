#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class invoice{
    public:
    int number;
    int totalMiliSeconds;
    int totalMinutes = 0;
    int totalPrice;

    void printInvoice();
};

void invoice::printInvoice(){
    cout << "phoneNumber: " << number << endl;
    cout << "totalMinutes: " << totalMinutes << endl;
    cout << "price for this duration: " << totalPrice << endl;
    
}

class dateClass{
    public:
    int day;
    int month;
    int year;

    void convertFromInt(int date);
    void printDate(){
        cout << year << "-" << month << " - " << day << endl;
    }
};
void dateClass::convertFromInt(int date){
    int tempDate = date;
    day = tempDate % 100;
    tempDate = tempDate / 100;
    month = tempDate % 100;
    year = tempDate / 100;
}

class timeClass{
    public:
    int minutes;
    int hours;
};

class phoneCall{
    private:
    int reciver;
    int caller;
    int dateData;
    dateClass date;
    int timeData;
    timeClass time;
    int duration;
    

    public:
    void getData(string file, int index);
    void printInfo();
    void getYYMMDD();
    void formatTime();
    int copyCaller();
    int copyDuration();
    int copyDate();
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

    myFile >> caller >> c >> reciver >> c >> duration >> c >> dateData >> c >> timeData >> c;

    getYYMMDD();
    formatTime();
    myFile.close();

}

void phoneCall::printInfo(){
    cout << "caller: " << caller << endl;
    cout << "reciver: " << reciver << endl;
    cout << "call duration: " << duration << endl;
    cout << "date: " << date.day << "/" << date.month << "-" << date.year << endl;
    cout << "time: " << time.hours << ":" << time.minutes << endl;
}

void phoneCall::getYYMMDD(){
    int tempDate = dateData;
    date.day = tempDate % 100;
    tempDate = tempDate / 100;
    date.month = tempDate % 100;
    date.year = tempDate / 100;
}

void phoneCall::formatTime(){
    int tempTime = timeData;
    time.minutes = tempTime % 100;
    time.hours = tempTime / 100;
}

int phoneCall::copyCaller(){
    return caller;
}

int phoneCall::copyDuration(){
    return duration;
}

int phoneCall::copyDate(){
    return dateData;
}

#endif