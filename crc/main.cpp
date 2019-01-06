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
    const string outputFile = fixOutputName(argv);
    bool validArguments = checkIfValidArguments(argv);

    const string inputFile = argv[1];

    if (validArguments != true){
        cout << "program is quitting" << endl;
        exit(EXIT_FAILURE);
    }


    int linesAmount = countLines(inputFile);        //counts amount of lines on cdr file i.e. how many calls the cdr contains.
    vector<phoneCall> call (linesAmount);

    for (int i = 0; i < linesAmount; i++){                                      //gather data to the objects.
        call[i].getData(inputFile, i);
    }

    sort(call.begin(), call.end(), [ ]( const auto& left, const auto& right )   //sort phonecalls by phoneNumber, lowest to highest.
    {
        return left.publicNumber < right.publicNumber;
    });

    int amountOfCallers = countAmountOfCallers(call, linesAmount);
    vector <invoice> invoiceArray(amountOfCallers);
    
    assignNumbersToInvoices(call, invoiceArray, linesAmount);               //assigning all MSISN numbers to the invoice objects

    int amountOfMonths = calculateAmountOfMonths(call, linesAmount);

    setInvoiceMonths(invoiceArray, call, amountOfMonths, linesAmount, amountOfCallers);

    
    for (int invoiceIteration = 0; invoiceIteration < amountOfCallers; invoiceIteration++){
        for (int dateIteration = 0; dateIteration < amountOfMonths; dateIteration++){
            for (int callIteration = 0; callIteration < linesAmount; callIteration++){
                if (call[callIteration].copyCaller() == invoiceArray[invoiceIteration].copyNumber() && call[callIteration].yearMonthValue == invoiceArray[invoiceIteration].yearMonthValue[dateIteration]){
                    invoiceArray[invoiceIteration].totalDurationPerMonth[dateIteration] += call[callIteration].copyDuration();
                }
            }
        }
        invoiceArray[invoiceIteration].setTotal();
    }

    system("pause");

    createInvoice(invoiceArray, outputFile);

    return 0;
}


