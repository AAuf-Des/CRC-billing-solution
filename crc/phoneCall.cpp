#include "..\include\phoneCall.h"
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

/*------------------------------ setters ------------------------------*/
/*---------- used to assign values to variables in the class ----------*/


//used to collect the data from the cdr file and store each line in invoice objects.
//index is used to skip over the lines that we have already read.

void phoneCall::setData(string file, int index){
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

    myFile >> caller >> c >> receiver >> c >> epochTime >> c >> durationMiliseconds >> c;

    publicNumber = caller;
    convertEpochToDate();
    setYearMonthValue();
    myFile.close();
}

//converts time_t to struc tm and saves it.
void phoneCall::convertEpochToDate(){
    date = *gmtime(&epochTime);

    date.tm_mon += 1;
    date.tm_year += 1900;
}

//convert struc tm to yearmonth value* <- readme.txt
void phoneCall::setYearMonthValue(){
    yearMonthValue = (date.tm_year * 100) + date.tm_mon;
}


/*--------------------------------- gettes ---------------------------------*/
/*------------------ copy/assign private member variables ------------------*/

long long int phoneCall::getCaller(){
    return caller;
}

int phoneCall::getDurationMiliseconds(){
    return durationMiliseconds;
}

time_t phoneCall::getEpochTime(){
    return epochTime;
}

int phoneCall::getYearMonthValue(){
    return yearMonthValue;
}