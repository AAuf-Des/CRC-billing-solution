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
    int yearMonthValue;
    int durationMiliseconds;
    
    
    public:
    long long int publicNumber;     //fix this, needed for lamba function

    void getData(string file, int index);
    void setYearMonthValue();
    void epochToDate();
    
    //copy functions
    long long int copyCaller();
    int copyDurationMiliseconds();
    int copyEpochTime();
    int copyYearMonthValue();

    //print
    void printInfo();
};

#endif