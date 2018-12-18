#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <windows.h>
#include "class.h"

using namespace std;

const string file = "cdr.txt";

int countLines(string file);
void getInvoice(int amountOfLines, phoneCall call[], invoice &invoice);
int getFirstDate(phoneCall call[], int amountOfLines);
int getLastDate(phoneCall call[], int amountOfLines);

int main()
{
    int linesAmount = countLines(file);
    phoneCall *call = new phoneCall[linesAmount];

    for (int i = 0; i < linesAmount; i++){
        call[i].getData(file, i);
    }

    dateClass firstDate;
    dateClass lastDate;
    
    int firstDateNumber;
    int lastDateNumber;
    firstDateNumber = getFirstDate(call, linesAmount);
    firstDate.convertFromInt(firstDateNumber);

    lastDateNumber = getLastDate(call, linesAmount);
    lastDate.convertFromInt(lastDateNumber);


    cout << "first Date occuring in cdr: "; firstDate.printDate();
    cout << "last Date occuring in cdr: "; lastDate.printDate();


    
    //work in progress här under
    system("pause");
    system("cls");

    invoice invoice;
    getInvoice(linesAmount, call, invoice);

    invoice.printInvoice();

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

void getInvoice(int amountOfLines, phoneCall call[], invoice &invoice){
    int phoneNumber;
    int payPerMinute;

    cout << "For what phone number do you want to make a invoice? : ";
    cin >> phoneNumber;
    cout << "What is " << phoneNumber << "'s pay per minute? : ";
    cin >> payPerMinute;
    invoice.number = phoneNumber;

    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyCaller() == phoneNumber){
            invoice.totalMinutes = invoice.totalMinutes + call[i].copyDuration();
        }
    }
    invoice.totalPrice = invoice.totalMinutes*payPerMinute;
}

int getFirstDate(phoneCall call[], int amountOfLines){
    int firstDate = call[0].copyDate();
    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyDate() < firstDate){
            firstDate = call[i].copyDate();
        }
    }
    return firstDate;
}

int getLastDate(phoneCall call[], int amountOfLines){
    int lastDate = call[0].copyDate();
    for (int i = 0; i < amountOfLines; i++){
        if (lastDate < call[i].copyDate()){
            lastDate = call[i].copyDate();
        }
    }
    return lastDate;
}
