#ifndef INVOICE_H
#define INVOICE_H

#include <vector>
#include <string>
#include <ctime>
using namespace std;

class invoice{
    private:
    long long int number;

    //month related variables
    vector<int> yearMonthValue;
    vector<int> totalDurationPerMonth;
    vector<struct tm> invoiceDates;

    int totalDuration = 0;

    //time/duration variables but holds minutes instread of seconds
    double totalMinutesDuration = 0;
    vector <double> totalMinutesDurationPerMonth;

    //price related variables
    int amountOfCalls = 0;
    int totalStartPrice;
    double totalTimePrice;
    double totalPrice;

    

    public:

    //month related setters
    void setNumber(long long int x);
    void setAmountOfMonths(int amountOfMonths);
    void initializeDurationPerMonth(int durationThatMonth);
    void addDurationPerMonth(int monthIndex, int addedDuration);
    void setYearMonthValue();
    void setTmDate(int monthIndex, time_t tempMonth);


    void setTotalDuration();

    //convert miliseconds to minutes
    void convertToMinutes();
    void setTotalMinutesDuration();
    void setTotalMinutesDurationPerMonth();

    //price related setters
    void addCall();
    void setTotalStartPrice(double payPerCall);
    void setTotalTimePrice(double payPerMinute);
    void setTotalPrice();

    void printToJson(string outputFile, bool isLast);

    //getters / copy
    long long int getNumber();
    int getYearMonthValue(int monthIndex);
    int getTotalDurationPerMonth(int monthIndex);
    int getTotalDuration();
    int getAmountOfCalls();

    


};
#endif