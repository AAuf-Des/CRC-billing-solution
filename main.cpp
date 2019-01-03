#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "class.h"

using namespace std;

const string file = "CdrMonth.txt";

int countLines(string file);

int countAmountOfCallers(vector<phoneCall> call, int amountOfLines);

void assignNumbersToInvoices(vector<phoneCall> call, vector<invoice> &invoiceArray, int amountOfLines);

int calculateAmountOfMonths(vector<phoneCall> call, int linesAmount);

time_t getLastDate(vector<phoneCall> call, int amountOfLines);

time_t getFirstDate(vector<phoneCall> call, int amountOfLines);

void setInvoiceMonths(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers);



int main()
{
    int linesAmount = countLines(file);        //counts amount of lines on cdr file i.e. how many calls the cdr contains.
    vector<phoneCall> call (linesAmount);

    for (int i = 0; i < linesAmount; i++){                                      //gather data to the objects.
        call[i].getData(file, i);
    }

    sort(call.begin(), call.end(), [ ]( const auto& left, const auto& right )   //sort phonecalls by phoneNumber, lowest to highest.
    {
        return left.publicNumber < right.publicNumber;
    });

    for (int i = 0; i < linesAmount; i++){              //print all phonecalls, delete before relese
        call[i].printInfo();
    }

    system("pause");


    int amountOfCallers = countAmountOfCallers(call, linesAmount);
    vector <invoice> invoiceArray(amountOfCallers);

    assignNumbersToInvoices(call, invoiceArray, linesAmount);               //assigning all MSISN numbers to the invoice objects

    int amountOfMonths = calculateAmountOfMonths(call, linesAmount);

    cout << "amountOfMonths: " << amountOfMonths << endl;

    setInvoiceMonths(invoiceArray, call, amountOfMonths, linesAmount, amountOfCallers);

    for (int i = 0; i < amountOfCallers; i++){
        invoiceArray[i].printInfo();
    }





    system("pause");


    /*
    for (int i = 0; i < amountOfCallers; i++){
        for (int j = 0; j < 3; j++){
            invoiceArray[i].lastDates[j] = lastDatesInCdr[j];
        }
        invoiceArray[i].getYearMonthValue();
    }

    //getting total durations from all phonecalls to last 3 months 
    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        for (int lastDateIteration = 0; lastDateIteration < 3; lastDateIteration++){
            for (int callIteration = 0; callIteration < linesAmount; callIteration++){
                if (call[callIteration].copyCaller() == invoiceArray[invoiceIteration].copyNumber() && call[callIteration].yearMonthValue == invoiceArray[invoiceIteration].yearMonthValue[lastDateIteration]){
                    invoiceArray[invoiceIteration].totalDurationPerMonth[lastDateIteration] += call[callIteration].copyDuration();
                }
            }
        }
    }

    

    for (int i = 0; i < amountOfCallers; i++){                      //print all invoice info,delete before release
        invoiceArray[i].printInfo();
    }
    */

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
    time_t oneMonth = 2628000;

    time_t tempMonth = first;

    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        invoiceArray[invoiceIteration].setAmountOfMonths(amountOfMonths);

        for(int monthIteration = 0; monthIteration < amountOfMonths; monthIteration++){
            invoiceArray[invoiceIteration].invoiceDates[monthIteration] = *gmtime(&tempMonth);

            invoiceArray[invoiceIteration].invoiceDates[monthIteration].tm_year += 1900;
            invoiceArray[invoiceIteration].invoiceDates[monthIteration].tm_mon += 1;
            //invoiceArray[invoiceIteration].invoiceDates[monthIteration].tm_mday = 15;
            tempMonth += oneMonth;
        }
        tempMonth = first;
    }
}

