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


//-----------------------------------------------------------------------------------------//
//hub function, calls other functions that sets up the invoice objects.

void setupInvoices(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfLines, int amountOfCallers, const double payPerCall, const double payPerMinute){

    assignNumbersToInvoices(call, invoiceArray, amountOfLines);

    int amountOfMonths = calculateAmountOfMonths(call, amountOfLines);

    setInvoiceMonths(invoiceArray, call, amountOfMonths, amountOfLines, amountOfCallers);

    assignCallsToInvoices(invoiceArray, call, amountOfMonths, amountOfLines, amountOfCallers);

    calculateFinalTotalPrice(invoiceArray, payPerCall, payPerMinute);

}

//------------------------------------------------------------------------------------------//

//function #1 in setupInvoices()
void assignNumbersToInvoices(vector<phoneCall> call, vector<invoice> &invoiceArray, int amountOfLines){
    int invoiceNumber = 0;
    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyCaller() != call[i+1].copyCaller()){
            invoiceArray[invoiceNumber].setNumber(call[i].copyCaller());
            invoiceNumber++;
        }
    }
}

//function #2 in setupInvoices()
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
void setInvoiceMonths(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers){
    time_t first = getFirstDate(call, amountOfLines);
    time_t last = getLastDate(call, amountOfLines);
    const time_t oneMonth = 2628000;

    struct tm firstDateMidMonth = *gmtime(&first);
    firstDateMidMonth.tm_mday = 15;
    time_t tempMonth = mktime(&firstDateMidMonth);                          //setting the first date in cdr to the same year and month but on 15th day of that month

    for (int i = 0; i < amountOfCallers; i++){
        invoiceArray[i].setAmountOfMonths(amountOfMonths);
        
        for(int monthIteration = 0; monthIteration < amountOfMonths; monthIteration++){

            invoiceArray[i].setTmDate(monthIteration, tempMonth);
            
            tempMonth += oneMonth;
            invoiceArray[i].getYearMonthValue();
            invoiceArray[i].initializeDurationPerMonth(0);
        }
        tempMonth = first;
    }
}

//function #4 in setupInvoices()
void assignCallsToInvoices(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers){

    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        for (int dateIteration = 0; dateIteration < amountOfMonths; dateIteration++){
            for (int callIteration = 0; callIteration < amountOfLines; callIteration++){
                if (call[callIteration].copyCaller() == invoiceArray[invoiceIteration].copyNumber() && call[callIteration].copyYearMonthValue() == invoiceArray[invoiceIteration].copyYearMonthValue(dateIteration)){
                    invoiceArray[invoiceIteration].addDurationPerMonth(dateIteration, call[callIteration].copyDurationMiliseconds());
                    invoiceArray[invoiceIteration].addCall();
                }
                
            }
        }
    }

}
//function #5 in setupInvoices()
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
time_t getLastDate(vector<phoneCall> call, int amountOfLines){
    int lastDate = call[0].copyEpochTime();
    for (int i = 0; i < amountOfLines; i++){
        if (lastDate < call[i].copyEpochTime()){
            lastDate = call[i].copyEpochTime();
        }
    }
    return lastDate;
}

//helperfunction for function #2 & #3 in setupInvoices
time_t getFirstDate(vector<phoneCall> call, int amountOfLines){
    int firstDate = call[0].copyEpochTime();
    for (int i = 0; i < amountOfLines; i++){
        if (firstDate > call[i].copyEpochTime()){
            firstDate = call[i].copyEpochTime();
        }
    }
    return firstDate;
}



//creates jsonflie and prints object data to it.
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

        invoiceArray[i].toJson(outputFile, isLast);
    }

    myFile.open(outputFile, std::ios::app);
    myFile << "\t]" << endl;
    myFile << "\t}" << endl;

    myFile.close();
}