#ifndef CLASS_H
#define CLASS_H
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
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

void invoice::toJson(string outputFile, bool isLast){
    ofstream myFile;
    myFile.open(outputFile, std::ios::app);

    myFile << "\t {" << endl;
    myFile << "\t\"MSIDN\":\" " << number << "\"," << endl;
    for (int i = 0; i < invoiceDates.size(); i++){
        myFile << "\t  \"" << invoiceDates[i].tm_year << "-" << invoiceDates[i].tm_mon << "\" :";
        myFile << totalDurationPerMonth[i] << "," << endl;
    }
    myFile << "\t  \"Total\": " << totalDuration << endl;

    if (isLast == true){
        myFile << "\t }" << endl;
    }
    else {
        myFile << "\t }," << endl;
    }

    

    myFile.close();
}

void invoice::setTotal(){
    for (int i = 0; i < invoiceDates.size(); i++){
        totalDuration = totalDuration + totalDurationPerMonth[i];
    }
}

void invoice::setAmountOfMonths(int amountOfMonths){
    invoiceDates.resize(amountOfMonths);
    totalDurationPerMonth.resize(amountOfMonths);
    yearMonthValue.resize(amountOfMonths);
}


void invoice::getYearMonthValue(){
    for (int i = 0; i < invoiceDates.size(); i++){
        yearMonthValue[i] = (invoiceDates[i].tm_year * 100) + invoiceDates[i].tm_mon;
    }
}

void invoice::setNumber(long long int x){
    number = x;
}

long long int invoice::copyNumber(){
    return number;
}

void invoice::printInfo(){
    cout << "MSIDN: " << number << endl;
    for (int i = 0; i < invoiceDates.size(); i++){
        cout << invoiceDates[i].tm_year << " " << invoiceDates[i].tm_mon << " - " << totalDurationPerMonth[i] << endl;
    }
    cout << "total Duration: " << totalDuration << endl;
    cout << "__________________________" << endl;
}







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



void phoneCall::getData(string file, int index){
    int count = 0;
    string line;
    char c;
    int i = 0;
    ifstream myFile;
    myFile.open(file);
    while (count < index){
        getline(myFile, line);
        count++;
    }

    myFile >> caller >> c >> reciver >> c >> epochTime >> c >> duration >> c;

    publicNumber = caller;
    epochToDate();
    getYearMonthValue();
    myFile.close();
}

void phoneCall::epochToDate(){
    date = *gmtime(&epochTime);

    date.tm_mon += 1;
    date.tm_year += 1900;
}

void phoneCall::getYearMonthValue(){
    yearMonthValue = (date.tm_year * 100) + date.tm_mon;
}

void phoneCall::printInfo(){
    cout << "caller: " << caller << endl;
    cout << "reciver: " << reciver << endl;
    cout << "call duration: " << duration << endl;
    cout << "date: " << date.tm_year << "-" << date.tm_mon << "-" << date.tm_mday << endl;
    cout << "YYYYMM int format: " << yearMonthValue << endl;
    cout << "_____________________________________________________________" << endl;

}


long long int phoneCall::copyCaller(){
    return caller;
}

int phoneCall::copyDuration(){
    return duration;
}

int phoneCall::copyEpochTime(){
    return epochTime;
}


#endif