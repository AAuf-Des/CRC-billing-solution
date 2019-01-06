#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "..\include\phoneCall.h"
#include "..\include\invoice.h"
#include "..\include\declarations.h"

using namespace std;

int main(int argc, const char * argv[])
{
    if (argc != 5){                                                            //check so that user dont input to many or to few 
        cout << "error: invalid amount of arguments" << endl;                   //or to many arguments
        exit(EXIT_FAILURE);
    }
    const string outputFile = fixOutputName(argv);
    const string smallOutputFile = fixSmallOutputName(argv);
    bool validArguments = checkIfValidArguments(argv);

    const string inputFile = argv[1];

    if (validArguments != true){
        cout << "program is quitting" << endl;
        exit(EXIT_FAILURE);
    }

    const double payPerCall = atof(argv[3]);
    const double payPerMinute = atof(argv[4]);

    int linesAmount = countLines(inputFile);                                    //counts amount of lines on cdr file i.e. how many calls the cdr contains.
    vector<phoneCall> call (linesAmount);                                       //create vector of phoneCalls

    for (int i = 0; i < linesAmount; i++){                                      //gather data from CDR to the objects.
        call[i].setData(inputFile, i);
    }

    sort(call.begin(), call.end(), [ ]( const auto& left, const auto& right )   //sort phonecalls by phoneNumber, lowest to highest.
    {
        return left.publicNumber < right.publicNumber;
    });

    int amountOfCallers = countAmountOfCallers(call, linesAmount);

    vector <invoice> invoiceArray(amountOfCallers);                             //create 1 invoice object for each caller (uniqe phonenumber) on the cdr
    
    setupInvoices(invoiceArray, call, linesAmount, amountOfCallers, payPerCall, payPerMinute);              
    //create fullscale invoice that contain all months.
    createInvoice(invoiceArray, outputFile);

    createSmallInvoice(invoiceArray, smallOutputFile);

    return 0;
}


