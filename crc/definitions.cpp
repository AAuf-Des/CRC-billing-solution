#include "..\include\declarations.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;



int countLines(string file){
    int count = 0;
    string str;
    ifstream myFile;
    myFile.open(file);
    while (getline(myFile, str)){
        count++;
    }

    myFile.close();
    return count;
}

int countAmountOfCallers(vector<phoneCall> call, int amountOfLines){
    int count = 0;

    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyCaller() != call[i+1].copyCaller()){
            count++;
        }
    }
    return count;
}

void assignNumbersToInvoices(vector<phoneCall> call, vector<invoice> &invoiceArray, int amountOfLines){
    int invoiceNumber = 0;
    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyCaller() != call[i+1].copyCaller()){
            invoiceArray[invoiceNumber].setNumber(call[i].copyCaller());
            invoiceNumber++;
        }
    }
}

int calculateAmountOfMonths(vector<phoneCall> call, int linesAmount){
    time_t lastEpochDateInCdr = getLastDate(call, linesAmount);
    time_t firstEpochDateInCdr = getFirstDate(call, linesAmount);
    struct tm firstTmDateInCdr = *gmtime(&firstEpochDateInCdr);
    struct tm lastTmDateInCdr = *gmtime(&lastEpochDateInCdr);

    int yearsAppart = lastTmDateInCdr.tm_year - firstTmDateInCdr.tm_year;
    int monthsAppart = lastTmDateInCdr.tm_mon - firstTmDateInCdr.tm_mon ;

    int totalMonths = (yearsAppart * 12) + monthsAppart + 1;

    return totalMonths;
}


time_t getLastDate(vector<phoneCall> call, int amountOfLines){
    int lastDate = call[0].copyEpochTime();
    for (int i = 0; i < amountOfLines; i++){
        if (lastDate < call[i].copyEpochTime()){
            lastDate = call[i].copyEpochTime();
        }
    }
    return lastDate;
}

time_t getFirstDate(vector<phoneCall> call, int amountOfLines){
    int firstDate = call[0].copyEpochTime();
    for (int i = 0; i < amountOfLines; i++){
        if (firstDate > call[i].copyEpochTime()){
            firstDate = call[i].copyEpochTime();
        }
    }
    return firstDate;
}


void setInvoiceMonths(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers){
    time_t first = getFirstDate(call, amountOfLines);
    time_t last = getLastDate(call, amountOfLines);
    long long int diff = difftime(last, first);
    const time_t oneMonth = 2628000;

    time_t tempMonth = first;

    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        invoiceArray[invoiceIteration].setAmountOfMonths(amountOfMonths);
        
        for(int monthIteration = 0; monthIteration < amountOfMonths; monthIteration++){
            invoiceArray[invoiceIteration].invoiceDates[monthIteration] = *gmtime(&tempMonth);

            invoiceArray[invoiceIteration].invoiceDates[monthIteration].tm_year += 1900;
            invoiceArray[invoiceIteration].invoiceDates[monthIteration].tm_mon += 1;
            tempMonth += oneMonth;

            invoiceArray[invoiceIteration].getYearMonthValue();
            invoiceArray[invoiceIteration].totalDurationPerMonth[monthIteration] = 0;

        }
        tempMonth = first;
    }
}

void createInvoice(vector<invoice> invoiceArray, string outputFile ){
    ofstream myFile;
    myFile.open(outputFile);
    myFile << "{" << endl;
    myFile << "\t\"Invoices\":[" << endl;
    myFile.close();

    bool isLast = false;
    for (int i = 0; i < invoiceArray.size(); i++){
        if (i == invoiceArray.size() - 1)
            isLast = true;

        invoiceArray[i].toJson(outputFile, isLast);
    }

    myFile.open(outputFile, std::ios::app);
    myFile << "\t]" << endl;
    myFile << "\t}" << endl;

    myFile.close();
}