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

    double totalMinutesDuration = 0;
    vector <double> totalMinutesDurationPerMonth;

    int amountOfCalls = 0;
    int totalStartPrice;
    double totalTimePrice;

    double totalPrice;

    

    public:

    //setters
    void setNumber(long long int x);
    void setAmountOfMonths(int amountOfMonths);
    void initializeDurationPerMonth(int durationThatMonth);
    void addDurationPerMonth(int monthIndex, int addedDuration);
    void getYearMonthValue();
    void setTmDate(int monthIndex, time_t tempMonth);
    void setTotalDuration();
    void setTotalStartPrice(int payPerCall);
    void setTotalTimePrice(double payPerMinute);
    void setTotalPrice();

    

    void addCall();


    //convert miliseconds to minutes
    void convertToMinutes();
    void getTotalMinutesDuration();
    void getTotalMinutesDurationPerMonth();

    void toJson(string outputFile, bool isLast);

    long long int copyNumber();
    int copyYearMonthValue(int monthIndex);
    int copyTotalDurationPerMonth(int monthIndex);
    int copyTotalDuration();
    int copyAmountOfCalls();
    int copyTotalTimePrice();

    void printInfo();
    


};
#endif