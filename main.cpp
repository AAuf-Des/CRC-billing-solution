#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include "class.h"

using namespace std;

const string file = "cdrDbgTest.txt";

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
    /*
    for (int i = 0; i < linesAmount; i++){
        call[i].printInfo();
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


