#include <iostream>
#include <vector>
#include <time.h>
#include <climits>

using namespace std;

vector<int> makeArray(int n, int min, int max) {
    vector<int> toReturn;
    for (int i=0; i<n; ++i) {
        toReturn.push_back(rand() % (max + min) + min);
    }
    return toReturn;
}

void print(const vector<int> &arr, string message) {
    cout << message;
    for (int num : arr) {
        cout << ' ' << num;
    }
    cout << endl;
}

void merge(vector<int> &arr, int start, int middle, int end) {
    int leftSize = middle - start;
    int rightSize = end - middle;
    int leftArr[leftSize + 1];
    int rightArr[rightSize + 1];
    for (int i=0; i<leftSize; ++i) {
        leftArr[i] = arr[start + i];
    }
    for (int i=0; i<rightSize; ++i) {
        rightArr[i] = arr[middle + i];
    }
    leftArr[leftSize] = INT_MAX;
    rightArr[rightSize] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k=start; k<end; ++k) {
        if (leftArr[i] < rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
    }
}

void mergeSort(vector<int> &arr, int start, int end) {
    if (start >= end - 1) {
        return;
    }
    int middle = (end - start) / 2 + start;
    mergeSort(arr, start, middle);
    mergeSort(arr, middle, end);
    merge(arr, start, middle, end);
}

void mergeSort(vector<int> &arr) {
    mergeSort(arr, 0, arr.size());
}

int main() {
    srand(time(NULL));
    vector<int> arr = makeArray(10, 1, 11);
    print(arr, "Before:");
    mergeSort(arr);
    print(arr, "After: ");
}

