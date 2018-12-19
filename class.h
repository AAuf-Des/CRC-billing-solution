#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;


struct dateStr{
    public:
    int day;
    int month;
    int year;
    time_t epochTime;

    void epochToDate()
    {
        struct tm localTime;
        localTime = *localtime(&epochTime);
        day = localTime.tm_mday;
        month = localTime.tm_mon + 1;
        year = localTime.tm_year + 1900;
    }

    //used to asign dates
    void assignDate(struct tm readTime, int x){
        day = 1;
        month = readTime.tm_mon + x;
        year = readTime.tm_year + 1900;
        if (month <= 0){
            month = month + 12;
            year = year - 1;
        }

    }

    void printDate(){
        cout << year << "-" << month << "-" << day << endl;
    }
};



//invoice class
class invoice{
    private:
    long long int number;

    public:
    dateStr lastDates[3];
    int yearMonthValue[3];
    int totalDurationPerMonth[3];
    
    void getNumber(long long int x);
    void printInfo();
    void getYearMonthValue();

    long long int copyNumber();
};

void invoice::getYearMonthValue(){
    yearMonthValue[0] = (lastDates[0].year * 100) + lastDates[0].month;
    yearMonthValue[1] = (lastDates[1].year * 100) + lastDates[1].month;
    yearMonthValue[2] = (lastDates[2].year * 100) + lastDates[2].month;
}

void invoice::getNumber(long long int x){
    number = x;
}

void invoice::printInfo(){
    cout << "MSISDN: " << number << endl;
    lastDates[0].printDate();
    lastDates[1].printDate();
    lastDates[2].printDate();
    cout << endl;
    cout << "yearMonthValues: " << yearMonthValue[0] << ", " << yearMonthValue[1] << ", " << yearMonthValue[2] << endl;
    cout << "________________________" << endl;
}

long long int invoice::copyNumber(){
    return number;
}



//phonecall class
class phoneCall{
    private:
    long long int reciver;
    long long int caller;
    time_t epochTime;
    dateStr date;
    int duration;
    

    public:
    long long int pCaller;
    int yearMonthValue;
    void getData(string file, int index);
    void printInfo();
    void epochToDate();
    void getYearMonthValue();
    

    //copy functions, return caller, duration etc etc..
    long long int copyCaller();
    int copyDuration();
    int copyEpochTime();
    int copyMonth();
    int copyYear();
};


void phoneCall::getYearMonthValue(){
    yearMonthValue = (date.year * 100) + date.month;
}

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

    pCaller = caller;

    epochToDate();
    getYearMonthValue();
    myFile.close();

}

void phoneCall::printInfo(){
    cout << "caller: " << caller << endl;
    cout << "reciver: " << reciver << endl;
    cout << "call duration: " << duration << endl;
    cout << "date: " << date.year << "-" << date.month << "-" << date.day << endl;
    cout << "YYYYMM int format: " << yearMonthValue << endl;
    cout << "_____________________________________________________________" << endl;

}

void phoneCall::epochToDate(){
    struct tm localTime;
    localTime = *localtime(&epochTime);


    date.day = localTime.tm_mday;
    date.month = localTime.tm_mon + 1;
    date.year = localTime.tm_year + 1900;
}

long long int phoneCall::copyCaller(){
    return caller;
}

int phoneCall::copyDuration(){
    return duration;
}

int phoneCall::copyEpochTime(){
    return epochTime;
}

int phoneCall::copyMonth(){
    return date.month;
}
    
int phoneCall::copyYear(){
    return date.year;
}

#endif