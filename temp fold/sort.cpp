#include <iostream>
#include <algorithm>
using namespace std;

int main(){

    int nums[6] = {6, 4, 3, 2, 5, 1};

    cout << "pre sorting: " << endl;
    for (int i = 0; i < 6; i++){
        cout << nums[i] << endl;
    }
    size_t size = sizeof(nums)/sizeof(nums[0]);

    sort(nums, nums+size);

    cout << "post sorting: " << endl;
    for (int i = 0; i < 6; i++){
        cout << nums[i] << endl;
    }

    system("pause");
    return 0;

}
