#include<iostream>
#include<chrono>
#include<time.h>
#include<algorithm>

using namespace std;

void InsertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void QuickSort(int* arr, const int left, const int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot) 
            i++;
        while (arr[j] > pivot) 
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) 
        QuickSort(arr, left, j);
    if (i < right)
        QuickSort(arr, i, right);
    
}

void Heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) 
        largest = left;
    if (right < n && arr[right] > arr[largest]) 
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        Heapify(arr, n, largest);
    }
}
void HeapSort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) 
        Heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

void randomizeArray(int* arr, int capacity) {
    srand(time(NULL));
    for (int i = 0; i < capacity; i++) {
        arr[i] = rand() % 50000 + 1;
    }
}

int main() {
    cout << "Please enter the number of elements: ";
    int n;
    cin >> n;
    int *arr = new int[n];
    int *question = new int[n];

    randomizeArray(arr, n); 
    copy(arr, arr + n, question);

    // cout << "Unsorted array: ";
    // for (int i = 0; i < n; i++)
    //     cout << arr[i] << " ";
    

    auto start1 = chrono::high_resolution_clock::now();
    QuickSort(arr, 0, n - 1);

    // cout << "Quick sort: ";
    // for (int i = 0; i < n; i++) 
    //     cout << arr[i] << " ";
    // cout << endl;

    auto end1 = chrono::high_resolution_clock::now();
    cout << "Quick sort Time taken: " << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << "ns" << endl;
    copy(question, question + n, arr);

    auto start2 = chrono::high_resolution_clock::now();
    InsertionSort(arr, n);

    // cout << "Insertion sort: ";
    // for (int i = 0; i < n; i++) 
    //      cout << arr[i] << " ";
    // cout << endl;

    auto end2 = chrono::high_resolution_clock::now();
    cout<< "Insertion sort Time taken: " << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << "ns" << endl;
    copy(question, question + n, arr);

    auto start3 = chrono::high_resolution_clock::now();
    HeapSort(arr, n);

    // cout << "Heap sort: ";
    // for (int i = 0; i < n; i++)
    //     cout << arr[i] << " ";
    // cout << endl;
    
    auto end3 = chrono::high_resolution_clock::now();
    cout << "Heap sort Time taken: " << chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count() << "ns" << endl;
    copy(question, question + n, arr);

    delete[] arr;
    return 0;
}