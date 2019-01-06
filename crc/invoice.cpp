#include "..\include\invoice.h"
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
using namespace std;


/*------------------------------ setters ------------------------------*/
/*---------- used to assign values to variables in the class ----------*/

//assign msisdn number to object.
void invoice::setNumber(long long int x){
    number = x;
}

//resize all vectors in invoice object.
void invoice::setAmountOfMonths(int amountOfMonths){
    invoiceDates.resize(amountOfMonths);
    totalDurationPerMonth.resize(amountOfMonths);
    yearMonthValue.resize(amountOfMonths);
    totalMinutesDurationPerMonth.resize(amountOfMonths);
}

//assign year month value to the invoice object
void invoice::setYearMonthValue(){
    for (int i = 0; i < invoiceDates.size(); i++){
        yearMonthValue[i] = (invoiceDates[i].tm_year * 100) + invoiceDates[i].tm_mon;
    }
}

//assign 0 to all indexes of the duration per month, to avoid problems when adding values to it.
void invoice::initializeDurationPerMonth(int durationThatMonth){
    for (int monthIteration = 0; monthIteration < totalDurationPerMonth.size(); monthIteration++){
        totalDurationPerMonth[monthIteration] = durationThatMonth;
    }
    
}

//adds a passed call duration to passed month number.
void invoice::addDurationPerMonth(int monthIndex, int addedDuration){
    totalDurationPerMonth[monthIndex] += addedDuration;
}

//converts time_t to struct tm, and gm time.
void invoice::setTmDate(int monthIndex ,time_t tempMonth){
    invoiceDates[monthIndex] = *gmtime(&tempMonth);

    invoiceDates[monthIndex].tm_year += 1900;
    invoiceDates[monthIndex].tm_mon += 1;

    setYearMonthValue();
}

//adds up all call durations for each month to get the total time in miliseconds
//for all the time that the cdr covers.
void invoice::setTotalDuration(){
    for (int i = 0; i < invoiceDates.size(); i++){
        totalDuration = totalDuration + totalDurationPerMonth[i];
    }
}

/*--------------------- minute converters & price setters ----------------------*/

/*------ minute converters ------*/

//calls the other to functions.
void invoice::convertToMinutes(){
    setTotalMinutesDuration();
    setTotalMinutesDurationPerMonth();
}

//converts the total amount of miliseconds to the total amount of minutes
void invoice::setTotalMinutesDuration(){
    totalMinutesDuration = (double)totalDuration / 60000;
}

//converts the totalAmountOfMiliseconds per every month and converts it to minutes.
void invoice::setTotalMinutesDurationPerMonth(){
    for (int i = 0; i < invoiceDates.size(); i++){
        totalMinutesDurationPerMonth[i] = (double)totalDurationPerMonth[i] / 60000;
    }
}



/*------ price setters ------*/

//increase amount of phonecalls by one.
void invoice::addCall(){
    amountOfCalls++;
}


//multiply the amount of calls with the price to start a phonecall.
void invoice::setTotalStartPrice(double payPerCall){
    totalStartPrice = amountOfCalls * payPerCall;
}


//multiply the total amount of minutes with the price per minute.
void invoice::setTotalTimePrice(double payPerMinute){
    totalTimePrice = totalMinutesDuration * payPerMinute;
}


//adds the total price for all minutes on the phone and price for all startup prices to 
//get total price for a custoer over all the months that the cdr covers.
void invoice::setTotalPrice(){
    totalPrice = (double) totalStartPrice + (double) totalTimePrice;
}



/*--------------------------------- gettes ---------------------------------*/
/*------------------ copy/assign private member variables ------------------*/

long long int invoice::getNumber(){
    return number;
}

int invoice::getYearMonthValue(int monthIndex){
    return yearMonthValue[monthIndex];
}

int invoice::getTotalDurationPerMonth(int monthIndex){
    return totalDurationPerMonth[monthIndex];
}

int invoice::getTotalDuration(){
    return totalDuration;
}

int invoice::getAmountOfCalls(){
    return amountOfCalls;
}

//prints info about a specific invoice object to a json file.
//the bool islast variable is so that we can know when we are on the last object to print, because the bracket after the last object is not supposed to
//have a comma like the rest.   example in .\bin\jsonTrail
void invoice::printToJson(string outputFile, bool isLast){
    ofstream myFile;
    myFile.open(outputFile, std::ios::app);

    myFile << "\t {" << endl;
    myFile << "\t  \"MSISDN\":\" " << number << "\"," << endl;
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


//same as above but only prints last 3 months 
void invoice::smallPrintToJson(string smallOutputFile, bool isLast){
    ofstream myFile;
    myFile.open(smallOutputFile, std::ios::app);

    myFile << "\t {" << endl;
    myFile << "\t  \"MSISDN\":\" " << number << "\"," << endl;
    for (int i = invoiceDates.size() - 3; i < invoiceDates.size(); i++){
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