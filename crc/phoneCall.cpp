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
    getYearMonthValue();
    myFile.close();
}

void phoneCall::epochToDate(){
    date = *gmtime(&epochTime);

    date.tm_mon += 1;
    date.tm_year += 1900;
}

void phoneCall::getYearMonthValue(){
    yearMonthValue = (date.tm_year * 100) + date.tm_mon;
}

void phoneCall::printInfo(){
    cout << "caller: " << caller << endl;
    cout << "reciver: " << reciver << endl;
    cout << "call duration: " << duration << endl;
    cout << "date: " << date.tm_year << "-" << date.tm_mon << "-" << date.tm_mday << endl;
    cout << "YYYYMM int format: " << yearMonthValue << endl;
    cout << "_____________________________________________________________" << endl;

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