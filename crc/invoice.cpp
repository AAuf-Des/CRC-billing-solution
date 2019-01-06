#include "..\include\invoice.h"
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;


void invoice::toJson(string outputFile, bool isLast){
    ofstream myFile;
    myFile.open(outputFile, std::ios::app);

    myFile << "\t {" << endl;
    myFile << "\t  \"MSIDN\":\" " << number << "\"," << endl;
    for (int i = 0; i < invoiceDates.size(); i++){
        myFile << "\t  \"" << invoiceDates[i].tm_year << "-" << invoiceDates[i].tm_mon << "\" :";
        myFile << totalMinutesDurationPerMonth[i] << "," << endl;
    }
    myFile << "\t  \"Total\": " << totalPrice << endl;

    if (isLast == true){
        myFile << "\t }" << endl;
    }
    else {
        myFile << "\t }," << endl;
    }

    myFile.close();
}

void invoice::setAmountOfMonths(int amountOfMonths){
    invoiceDates.resize(amountOfMonths);
    totalDurationPerMonth.resize(amountOfMonths);
    yearMonthValue.resize(amountOfMonths);
    totalMinutesDurationPerMonth.resize(amountOfMonths);
}


void invoice::getYearMonthValue(){
    for (int i = 0; i < invoiceDates.size(); i++){
        yearMonthValue[i] = (invoiceDates[i].tm_year * 100) + invoiceDates[i].tm_mon;
    }
}

void invoice::initializeDurationPerMonth(int durationThatMonth){
    for (int monthIteration = 0; monthIteration < totalDurationPerMonth.size(); monthIteration++){
        totalDurationPerMonth[monthIteration] = durationThatMonth;
    }
    
}

void invoice::addDurationPerMonth(int monthIndex, int addedDuration){
    totalDurationPerMonth[monthIndex] += addedDuration;
}

void invoice::setTmDate(int monthIndex ,time_t tempMonth){
    invoiceDates[monthIndex] = *gmtime(&tempMonth);

    invoiceDates[monthIndex].tm_year += 1900;
    invoiceDates[monthIndex].tm_mon += 1;

    getYearMonthValue();
}

void invoice::setNumber(long long int x){
    number = x;
}

void invoice::setTotalDuration(){
    for (int i = 0; i < invoiceDates.size(); i++){
        totalDuration = totalDuration + totalDurationPerMonth[i];
    }
}

void invoice::addCall(){
    amountOfCalls++;
}

void invoice::setTotalStartPrice(int x){
    totalStartPrice = amountOfCalls * x;
}

void invoice::setTotalTimePrice(double payPerMinute){
    totalTimePrice = totalMinutesDuration * payPerMinute;
}

void invoice::setTotalPrice(){
    totalPrice = (double) totalStartPrice + (double) totalTimePrice;
}




//getter
long long int invoice::copyNumber(){
    return number;
}

int invoice::copyYearMonthValue(int monthIndex){
    return yearMonthValue[monthIndex];
}

int invoice::copyTotalDurationPerMonth(int monthIndex){
    return totalDurationPerMonth[monthIndex];
}

int invoice::copyTotalDuration(){
    return totalDuration;
}


//totalMinutes

void invoice::convertToMinutes(){
    getTotalMinutesDuration();
    getTotalMinutesDurationPerMonth();
}
void invoice::getTotalMinutesDuration(){
    totalMinutesDuration = (double)totalDuration / 60000;
}

void invoice::getTotalMinutesDurationPerMonth(){
    for (int i = 0; i < invoiceDates.size(); i++){
        totalMinutesDurationPerMonth[i] = (double)totalDurationPerMonth[i] / 60000;
    }
}

int invoice::copyAmountOfCalls(){
    return amountOfCalls;
}


//print info

void invoice::printInfo(){
    cout << "MSIDN: " << number << endl;
    for (int i = 0; i < totalDurationPerMonth.size(); i++){
        cout << yearMonthValue[i] << "-" << totalMinutesDurationPerMonth[i] <<  endl;
    }
    cout << "amount of minutes: " << totalMinutesDuration << endl;
    cout << "amount of calls: " << amountOfCalls << endl;

    cout << "minutes price total: " << totalTimePrice << endl;
    cout << "start price total: " << totalStartPrice << endl;

    cout << "TOTAL PRICE: " << totalPrice << endl;
    
    cout << "______________________" << endl;
}