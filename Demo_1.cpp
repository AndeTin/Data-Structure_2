#include<fstream>
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

void Heapify(int* arr, int n, int root) {
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int largest = root;
    if (left < n && arr[left] > arr[right] && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[left] && arr[right] > arr[largest]) {
        largest = right;
    }
    if(largest != root) {
        swap(arr[root], arr[largest]);
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

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void MergeSort(int* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void randomizeArray(int* arr, int capacity) {
    srand(time(NULL));
    for (int i = 0; i < capacity; i++) {
        arr[i] = rand() % 50000 + 1;
    }
}


int main() {
    ofstream csvFile("sorting_times.csv");
    csvFile << "Number of Elements,QuickSort Time (ns),MergeSort Time (ns),HeapSort Time (ns),InsertionSort Time (ns)\n";

    const int minSize = 10;       // Starting size
    const int maxSize = 100000;  // Maximum size
    const int steps = 100;       // Number of data points
    const int trials = 10;       // Number of trials for averaging

    for (int step = 0; step < steps; step++) {
        int size = minSize + step * (maxSize - minSize) / (steps - 1); // Calculate size dynamically
        int *arr = new int[size];
        int *question = new int[size];

        long long totalQuickSortTime = 0;
        long long totalMergeSortTime = 0;
        long long totalHeapSortTime = 0;
        long long totalInsertionSortTime = 0;

        for (int t = 0; t < trials; t++) {
            randomizeArray(arr, size);
            copy(arr, arr + size, question);

            // QuickSort
            auto start1 = chrono::high_resolution_clock::now();
            QuickSort(arr, 0, size - 1);
            auto end1 = chrono::high_resolution_clock::now();
            totalQuickSortTime += chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
            copy(question, question + size, arr);

            // MergeSort
            auto start2 = chrono::high_resolution_clock::now();
            MergeSort(arr, 0, size - 1);
            auto end2 = chrono::high_resolution_clock::now();
            totalMergeSortTime += chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();
            copy(question, question + size, arr);

            // HeapSort
            auto start3 = chrono::high_resolution_clock::now();
            HeapSort(arr, size);
            auto end3 = chrono::high_resolution_clock::now();
            totalHeapSortTime += chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count();
            copy(question, question + size, arr);

            // InsertionSort
            auto start4 = chrono::high_resolution_clock::now();
            InsertionSort(arr, size);
            auto end4 = chrono::high_resolution_clock::now();
            totalInsertionSortTime += chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count();
        }

        // Calculate averages
        long long avgQuickSortTime = totalQuickSortTime / trials;
        long long avgMergeSortTime = totalMergeSortTime / trials;
        long long avgHeapSortTime = totalHeapSortTime / trials;
        long long avgInsertionSortTime = totalInsertionSortTime / trials;

        // Record results in CSV
        csvFile << size << "," << avgQuickSortTime << "," << avgMergeSortTime << "," << avgHeapSortTime << "," << avgInsertionSortTime << "\n";

        delete[] question;
        delete[] arr;
    }

    csvFile.close();
    cout << "Sorting times recorded in sorting_times.csv" << endl;
    return 0;
}
