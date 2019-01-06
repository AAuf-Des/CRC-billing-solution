#include "..\include\declarations.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
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



bool checkIfValidNumber(const char * argv[], int x){
    string input = argv[x];
    bool valid = true;

    for (int i = 0; i < input.size() && valid == true; i++){
        if (isdigit(input[i]) != true){
            cout << input[i] << endl;
            valid = false;
            cout << "error " << argv[x] << " is not a valid number for price model." << endl;
        }
    }

    return valid;
}


void fixArguments(const char * argv[], string &inputFile, string &outputFile){
    inputFile = argv[1];
    string argInput = argv[2];
    outputFile = "./bin/" + argInput + ".json";
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
    const time_t oneMonth = 2628000;

    struct tm firstDateMidMonth = *gmtime(&first);
    firstDateMidMonth.tm_mday = 15;
    time_t tempMonth = mktime(&firstDateMidMonth);                          //setting the first date in cdr to the same year and month but on 15th day of that month



    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        invoiceArray[invoiceIteration].setAmountOfMonths(amountOfMonths);
        
        for(int monthIteration = 0; monthIteration < amountOfMonths; monthIteration++){

            invoiceArray[invoiceIteration].setTmDate(monthIteration, tempMonth);
            
            tempMonth += oneMonth;

            invoiceArray[invoiceIteration].setTotalDurationPerMonth(monthIteration, 0);
            
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