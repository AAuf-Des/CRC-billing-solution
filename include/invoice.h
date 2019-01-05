#ifndef INVOICE_H
#define INVOICE_H

#include <vector>
#include <string>
#include <ctime>
using namespace std;

//invoice class
class invoice{
    private:
    long long int number;

    public:
    vector<struct tm> invoiceDates;
    vector<int> totalDurationPerMonth;
    vector<int> yearMonthValue;
    int totalDuration = 0;
    
    void setNumber(long long int x);
    void setAmountOfMonths(int amountOfMonths);
    void getYearMonthValue();
    void setTotal();
    void printInfo();

    void toJson(string outputFile, bool isLast);

    long long int copyNumber();


};
#endif