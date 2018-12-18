#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "class.h"

using namespace std;

const string file = "cdrSort.txt";

int countLines(string file);
int countAmountOfCallers(vector<phoneCall> call, int amountOfLines);

int main()
{
    int linesAmount = countLines(file);        //couts amount of lines on cdr file i.e. how many calls the cdr contains.
    vector<phoneCall> call (linesAmount);

    for (int i = 0; i < linesAmount; i++){                                      //gather data to the objects.
        call[i].getData(file, i);
    }

    sort(call.begin(), call.end(), [ ]( const auto& left, const auto& right )   //sort phonecalls by phoneNumber, lowest to highest.
    {
        return left.pCaller < right.pCaller;
    });
    /*
    for (int i = 0; i < linesAmount; i++){
        call[i].printInfo();
    }
    */

    int amountOfCallers = countAmountOfCallers(call, linesAmount);

    cout << "amount of callers: " << amountOfCallers << endl;






    
    return 0;
}



int countLines(string file){
    int count = 0;
    string str;
    ifstream myFile;
    myFile.open(file);
    while (getline(myFile, str)){
        count++;
    }

    myFile.close();
    return count;
}

int countAmountOfCallers(vector<phoneCall> call, int amountOfLines){
    int count = 0;

    for (int i = 0; i < amountOfLines; i++){
        if (call[i].copyCaller() != call[i+1].copyCaller()){
            count++;
        }
    }
    return count;
}




