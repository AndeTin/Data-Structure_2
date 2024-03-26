#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>

void randomizeArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        arr[i+1] = rand() % 50000 + 1;
    }
}

void InsertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void Quicksort(vector<int>& arr, int low, int high) {
    
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

    vector<int> arr(capacity + 1);
    randomizeArray(arr);
}