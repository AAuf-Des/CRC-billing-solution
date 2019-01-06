#ifndef PHONECALL_H
#define PHONECALL_H
#include <ctime>
#include <string>
using namespace std;

//phonecall class
class phoneCall{
    private:
    long long int reciver;
    long long int caller;
    time_t epochTime;
    struct tm date;
    int duration;
    

    public:
    long long int publicNumber;     //fix this, needed for lamba function
    int yearMonthValue;
    void getData(string file, int index);
    void printInfo();
    void getYearMonthValue();
    void epochToDate();
    

    //copy functions, return caller, duration etc etc..
    long long int copyCaller();
    int copyDuration();
    int copyEpochTime();
};

#endif