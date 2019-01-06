#include "..\include\phoneCall.h"
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

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

    publicNumber = caller;
    epochToDate();
    setYearMonthValue();
    myFile.close();
}

void phoneCall::epochToDate(){
    date = *gmtime(&epochTime);

    date.tm_mon += 1;
    date.tm_year += 1900;
}

void phoneCall::setYearMonthValue(){
    yearMonthValue = (date.tm_year * 100) + date.tm_mon;
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

int phoneCall::copyYearMonthValue(){
    return yearMonthValue;
}