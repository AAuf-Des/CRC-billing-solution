#ifndef DECLARATIONS_H
#define DECLARATIONS_H
#include <vector>
#include <string>
#include "phoneCall.h"
#include "invoice.h"
using namespace std;

const string fixOutputName(const char * argv[]);

const string fixSmallOutputName(const char * argv[]);

bool checkIfValidArguments(const char * argv[]);

bool checkIfFileExist(const char * argv[]);

bool checkIfValidNumber(const char * argv[], int x);

int countLines(string file);

int countAmountOfCallers(vector<phoneCall> call, int amountOfLines);

void assignNumbersToInvoices(vector<phoneCall> call, vector<invoice> &invoiceArray, int amountOfLines);

int calculateAmountOfMonths(vector<phoneCall> call, int linesAmount);

time_t getLastDate(vector<phoneCall> call, int amountOfLines);

time_t getFirstDate(vector<phoneCall> call, int amountOfLines);

void setInvoiceMonths(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers);

void createInvoice(vector<invoice> &invoiceArray, string outputFile);

void createSmallInvoice(vector<invoice> &invoiceArray, string smallOutputFile);


void setupInvoices(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfLines, int amountOfCallers, const double payPerCall, const double payPerMinute);

void assignCallsToInvoices(vector<invoice> &invoiceArray, vector<phoneCall> call, int amountOfMonths, int amountOfLines, int amountOfCallers);

void calculateFinalTotalPrice(vector<invoice> &invoiceArray, const double payPerCall, const double payPerMinute);

#endif