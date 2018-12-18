#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "class.h"

using namespace std;

const string file = "cdrDiv.txt";

int countLines(string file);
int countAmountOfCallers(vector<phoneCall> call, int amountOfLines);
void assignNumbersToInvoices(vector<phoneCall> call, invoice invoiceArray[], int amountOfLines);
time_t getLastDate(vector<phoneCall> call, int amountOfLines);
    

int main()
{
    int linesAmount = countLines(file);        //counts amount of lines on cdr file i.e. how many calls the cdr contains.
    vector<phoneCall> call (linesAmount);

    for (int i = 0; i < linesAmount; i++){                                      //gather data to the objects.
        call[i].getData(file, i);
    }

    sort(call.begin(), call.end(), [ ]( const auto& left, const auto& right )   //sort phonecalls by phoneNumber, lowest to highest.
    {
        return left.pCaller < right.pCaller;
    });

    int amountOfCallers = countAmountOfCallers(call, linesAmount);
    invoice *invoiceArray = new invoice[amountOfCallers];

    assignNumbersToInvoices(call, invoiceArray, linesAmount);

    dateStruct lastDatesInCdr[3];

    time_t epochTime = 1547156444;//getLastDate(call, linesAmount);
    struct tm readTime;
    readTime = *localtime(&epochTime);
    lastDatesInCdr[0].assignDate(readTime, 1);
    lastDatesInCdr[1].assignDate(readTime, 0);
    lastDatesInCdr[2].assignDate(readTime, -1);

    lastDatesInCdr[0].printDate();
    lastDatesInCdr[1].printDate();
    lastDatesInCdr[2].printDate();

    return 0;
}



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

void assignNumbersToInvoices(vector<phoneCall> call, invoice invoiceArray[], int amountOfLines){
    int invoiceNumber = 0;
    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyCaller() != call[i+1].copyCaller()){
            invoiceArray[invoiceNumber].getNumber(call[i].copyCaller());
            invoiceNumber++;
        }
    }
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
