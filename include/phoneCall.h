#ifndef PHONECALL_H
#define PHONECALL_H
#include <ctime>
#include <string>
using namespace std;

class phoneCall{
    private:
    //original metadata from CDR
    long long int receiver;
    long long int caller;
    time_t epochTime;
    struct tm date;

    //fixed extraData
    int yearMonthValue;
    int durationMiliseconds;
    
    
    public:
    long long int publicNumber;

    //setters
    void setData(string file, int index);
    void setYearMonthValue();
    void convertEpochToDate();
    
    //copy functions
    long long int getCaller();
    int getDurationMiliseconds();
    time_t getEpochTime();
    int getYearMonthValue();
};

#endif