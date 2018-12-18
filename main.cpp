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

int main()
{
    int linesAmount = countLines(file);
    //phoneCall *call = new phoneCall[linesAmount];
    vector<phoneCall> call(linesAmount);


    for (int i = 0; i < linesAmount; i++){
        call[i].getData(file, i);
    }
    //remove before relase.
    cout << "calls before sort" << endl;
    for (int i = 0; i < linesAmount; i++){
        call[i].printInfo();
    }

    //sorting algorithm
    sort(call.begin(), call.end(), [ ]( const auto& left, const auto& right )
    {
        return left.pCaller < right.pCaller;
    });

    system("pause");

    cout << "calls after sort" << endl;
    for (int i = 0; i < linesAmount; i++){
        call[i].printInfo();
    }  
    
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


