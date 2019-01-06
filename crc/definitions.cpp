#include "..\include\declarations.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;



//makes sure that input on argv[2] (outputfile name) is placed in proper folder and with proper file format.
const string fixOutputName(const char * argv[]){
    string argvStr = argv[2];

    if (argvStr.find(".json") == string::npos) {    
        argvStr += ".json";
    }

    if (argvStr.find("./bin/") == string::npos) {
        argvStr = "./bin/" + argvStr;
    }

    const string outPutFile = argvStr;

    return outPutFile;
}

//creates filename for the smaller.json file with only 3 months.
const string fixSmallOutputName(const char * argv[]){
    string argvStr = argv[2];

    argvStr += "_ThreeMonths";


    if (argvStr.find(".json") == string::npos) {    
        argvStr += ".json";
    }

    if (argvStr.find("./bin/") == string::npos) {
        argvStr = "./bin/" + argvStr;
    }

    const string outPutFile = argvStr;

    return outPutFile;
}

//check so that the argument that is supposed to be a path to the Cdr file and also check so that argv[3] & argv[4]
//does not contain letters. if one of these tests does not turn out valid, the program will return to main, and exit soon after.
//the helper functions also deliver error messages.
bool checkIfValidArguments(const char * argv[]){
    bool validArguments = checkIfFileExist(argv);

    if (validArguments == true){
        validArguments = checkIfValidNumber(argv, 3);
    }

    if (validArguments == true){
        validArguments = checkIfValidNumber(argv, 4);
    }

    return validArguments;

}

//checks so that the input file (cdr file) exist.
//helper function to checkIfValidArguments
bool checkIfFileExist(const char * argv[]){
    string str;
	bool fileExist;

    ifstream myFile(argv[1]);
    if (myFile.fail()){
        cout << "error: " << argv[1] << " does not exist." << endl;
		fileExist = false;
    }
    else{
		
        fileExist = true;
    }
    myFile.close();
    return fileExist;
}


//helper function to checkIfValidArguments
//checks so that the price arguments does not contain letters other than '.' if we need decimal.
bool checkIfValidNumber(const char * argv[], int x)
{
    string input = argv[x];

    bool valid = true;

    for (int i = 0; i < input.size() && valid == true; i++){
        if (isdigit(input[i]) == true){
            valid = true;
        }
        else if (input[i] == '.'){
            valid = true;
        }
        else {
            cout << "error: '" << argv[x] << "' is not a valid number for payment plan" << endl;
            valid = false;
        }
    }

    if (input.size() == 1 && input[0] == '.'){
        cout << "error: '" << argv[x] << "' is not a valid number for payment plan" << endl;
        valid = false;
    }

    return valid;
}


/*-------------------------------------------- count functions --------------------------------------------*/
/*------------------------ give the program information about how long the vectors -----------------------*/
/*----------------- should be, also useful for forloops etc. as we cant always use vector.size() --------*/

//returns how big the vector holding phonecalls should be.
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

//counts amount of unique numbers in the cdr witch is the same size as the invoice vector will have.
int countAmountOfCallers(vector<phoneCall> call, int amountOfLines){
    int count = 0;

    for (int i = 0; i < amountOfLines; i++){
        if (call[i].getCaller() != call[i+1].getCaller()){
            count++;
        }
    }
    return count;
}



/*------------------------------- invoice setup "hub function" ------------------------------*/
/*--------------------------- used and created to clear up main ----------------------------*/
/*--------------- calls and manages most function that prepares the invoice file ----------*/


void setupInvoices(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfLines, int amountOfCallers, const double payPerCall, const double payPerMinute){

    assignNumbersToInvoices(call, invoiceArray, amountOfLines);

    int amountOfMonths = calculateAmountOfMonths(call, amountOfLines);

    setInvoiceMonths(invoiceArray, call, amountOfMonths, amountOfLines, amountOfCallers);

    assignCallsToInvoices(invoiceArray, call, amountOfMonths, amountOfLines, amountOfCallers);

    calculateFinalTotalPrice(invoiceArray, payPerCall, payPerMinute);

}

//function #1 in setupInvoices()
//scrolls through the vector witch is sorted by number(caller), as it is sorted by number we can just scroll through them and
//when we find two numbers next to each other that is not the same we save the new one to a invoice object.
void assignNumbersToInvoices(vector<phoneCall> call, vector<invoice> &invoiceArray, int amountOfLines){
    int invoiceNumber = 0;
    for (int i = 0; i < amountOfLines; i++){
        if (call[i].getCaller() != call[i+1].getCaller()){
            invoiceArray[invoiceNumber].setNumber(call[i].getCaller());
            invoiceNumber++;
        }
    }
}

//function #2 in setupInvoices()
//calculates amount of months between the first and last date in the cdr.
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

//function #3 in setupInvoices()
//creates x amount of months and assign month and year values to them.
//readme.txt
void setInvoiceMonths(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers){
    time_t first = getFirstDate(call, amountOfLines);
    time_t last = getLastDate(call, amountOfLines);
    const time_t oneAverageMonth = 2628000;

    struct tm firstDateMidMonth = *gmtime(&first);
    firstDateMidMonth.tm_mday = 15;
    time_t tempMonth = mktime(&firstDateMidMonth);

    for (int i = 0; i < amountOfCallers; i++){
        invoiceArray[i].setAmountOfMonths(amountOfMonths);
        
        for(int monthIteration = 0; monthIteration < amountOfMonths; monthIteration++){

            invoiceArray[i].setTmDate(monthIteration, tempMonth);
            
            tempMonth += oneAverageMonth;
            invoiceArray[i].setYearMonthValue();
            invoiceArray[i].initializeDurationPerMonth(0);
        }
        tempMonth = first;
    }
}

//function #4 in setupInvoices()
//scroll through all invoices all dates and all calls, if a combination of call and invoice where the phonenumbers and the year+Month value
//is the same, we copy the duration of of the call to the proper invoice and to the proper duration per month vector.
//we also add a phonecall to that users invoice.
void assignCallsToInvoices(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers){

    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        for (int dateIteration = 0; dateIteration < amountOfMonths; dateIteration++){
            for (int callIteration = 0; callIteration < amountOfLines; callIteration++){
                if (call[callIteration].getCaller() == invoiceArray[invoiceIteration].getNumber() && call[callIteration].getYearMonthValue() == invoiceArray[invoiceIteration].getYearMonthValue(dateIteration)){
                    invoiceArray[invoiceIteration].addDurationPerMonth(dateIteration, call[callIteration].getDurationMiliseconds());
                    invoiceArray[invoiceIteration].addCall();
                }
                
            }
        }
    }

}
//function #5 in setupInvoices()
//calls a couple of nessecary invoice member functions. 
//all of these are explained in ./include/invoice.cpp
void calculateFinalTotalPrice(vector<invoice> &invoiceArray, const double payPerCall, const double payPerMinute){
    for (int i = 0; i < invoiceArray.size(); i++){
        invoiceArray[i].setTotalDuration();
        invoiceArray[i].convertToMinutes();

        invoiceArray[i].setTotalStartPrice(payPerCall);
        invoiceArray[i].setTotalTimePrice(payPerMinute);
        invoiceArray[i].setTotalPrice();

    }    
}


//helperfunction for function #2 & #3 in setupInvoices
//return the biggest epoch date in the call objects, witch is the last date to occur in the cdr.
time_t getLastDate(vector<phoneCall> call, int amountOfLines){
    int lastDate = call[0].getEpochTime();
    for (int i = 0; i < amountOfLines; i++){
        if (lastDate < call[i].getEpochTime()){
            lastDate = call[i].getEpochTime();
        }
    }
    return lastDate;
}

//helperfunction for function #2 & #3 in setupInvoices
//return the biggest epoch date in the call objects, witch is the last date to occur in the cdr.
time_t getFirstDate(vector<phoneCall> call, int amountOfLines){
    int firstDate = call[0].getEpochTime();
    for (int i = 0; i < amountOfLines; i++){
        if (firstDate > call[i].getEpochTime()){
            firstDate = call[i].getEpochTime();
        }
    }
    return firstDate;
}



//creates jsonflie and first we print the part that is not supposed to be printed for every object.
//the bool islast variable is so that we can know when we are on the last object to print, because the bracket after the last object is not supposed to
//have a comma like the rest.   example in .\bin\jsonTrail

//we also call the invoice member printToJson() for as many times as there are invoice objects in. all info about that function is in crc\invoice.cpp

void createInvoice(vector<invoice> &invoiceArray, string outputFile ){
    ofstream myFile;
    myFile.open(outputFile);
    myFile << "{" << endl;
    myFile << "\t\"Invoices\":[" << endl;
    myFile.close();

    bool isLast = false;
    for (int i = 0; i < invoiceArray.size(); i++){
        if (i == invoiceArray.size() - 1)
            isLast = true;

        invoiceArray[i].printToJson(outputFile, isLast);
    }

    myFile.open(outputFile, std::ios::app);
    myFile << "\t]" << endl;
    myFile << "\t}" << endl;

    myFile.close();
}


//same as above but only last 3 months.
void createSmallInvoice(vector<invoice> &invoiceArray, string smallOutputFile){
    ofstream myFile;
    myFile.open(smallOutputFile);
    myFile << "{" << endl;
    myFile << "\t\"Invoices\":[" << endl;
    myFile.close();

    bool isLast = false;
    for (int i = 0; i < invoiceArray.size(); i++){
        if (i == invoiceArray.size() - 1)
            isLast = true;

        invoiceArray[i].smallPrintToJson(smallOutputFile, isLast);
    }

    myFile.open(smallOutputFile, std::ios::app);
    myFile << "\t]" << endl;
    myFile << "\t}" << endl;

    myFile.close();
}