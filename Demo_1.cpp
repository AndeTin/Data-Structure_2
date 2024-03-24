#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>

void randomizeArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 50000 + 1;
    }

}

using namespace std;
int main() {
    int time = 0;
    int capacity = 0;
    srand(time(0));
    cout << "Please enter the capacity of the array: "<<endl;

    cint >> capacity;
    if (cin.fail()) {
        cout << "Invalid input. Please enter an integer for capacity." << endl;
        return 0;
    }
    else if (capacity <= 0 || capacity > 1000000) {
        cout << "Invalid input. Please enter an integer between 1 and 1000000 for capacity." << endl;
        return 0;
    }

    vector<int> arr(capacity);
    randomizeArray(arr);
}