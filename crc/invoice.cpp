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
    myFile << "\t\"MSIDN\":\" " << number << "\"," << endl;
    for (int i = 0; i < invoiceDates.size(); i++){
        myFile << "\t  \"" << invoiceDates[i].tm_year << "-" << invoiceDates[i].tm_mon << "\" :";
        myFile << totalDurationPerMonth[i] << "," << endl;
    }
    myFile << "\t  \"Total\": " << totalDuration << endl;

    if (isLast == true){
        myFile << "\t }" << endl;
    }
    else {
        myFile << "\t }," << endl;
    }

    

    myFile.close();
}

void invoice::setTotal(){
    for (int i = 0; i < invoiceDates.size(); i++){
        totalDuration = totalDuration + totalDurationPerMonth[i];
    }
}

void invoice::setAmountOfMonths(int amountOfMonths){
    invoiceDates.resize(amountOfMonths);
    totalDurationPerMonth.resize(amountOfMonths);
    yearMonthValue.resize(amountOfMonths);
}


void invoice::getYearMonthValue(){
    for (int i = 0; i < invoiceDates.size(); i++){
        yearMonthValue[i] = (invoiceDates[i].tm_year * 100) + invoiceDates[i].tm_mon;
    }
}

void invoice::setNumber(long long int x){
    number = x;
}

long long int invoice::copyNumber(){
    return number;
}

void invoice::printInfo(){
    cout << "MSIDN: " << number << endl;
    for (int i = 0; i < invoiceDates.size(); i++){
        cout << invoiceDates[i].tm_year << " " << invoiceDates[i].tm_mon << " - " << totalDurationPerMonth[i] << endl;
    }
    cout << "total Duration: " << totalDuration << endl;
    cout << "__________________________" << endl;
}