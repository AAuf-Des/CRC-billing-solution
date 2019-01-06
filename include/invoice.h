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
    vector<int> yearMonthValue;
    vector<int> totalDurationPerMonth;
    vector<struct tm> invoiceDates;
    int totalDuration = 0;
    

    public:

    void setNumber(long long int x);
    void setAmountOfMonths(int amountOfMonths);
    void setTotalDurationPerMonth(int monthIndex, int durationThatMonth);
    void addTotalDurationPerMonth(int monthIndex, int addedDuration);
    void getYearMonthValue();
    void setTotalDuration();
    void setTmDate(int monthIndex, time_t tempMonth);


    void toJson(string outputFile, bool isLast);

    long long int copyNumber();
    int copyYearMonthValue(int monthIndex);
    int copyTotalDurationPerMonth(int monthIndex);
    


};
#endif