#include <iostream>

using namespace std;

int partition(int arr[], int start, int end) {
    int lessThanIndex = start - 1;
    int splitValue = arr[end];
    for (int i=start; i<end; ++i) {
        if (arr[i] < splitValue) {
            ++lessThanIndex;
            swap(arr[i], arr[lessThanIndex]);
        }
    }
    int split = lessThanIndex + 1;
    swap(arr[end], arr[split]);
    return split;
}

int quickSelect(int arr[], int k, int start, int end) {
    int split = partition(arr, start, end);
    if (split == k) {
        return arr[k];
    }
    if (split < k) {
        return quickSelect(arr, k, split + 1, end);
    }
    return quickSelect(arr, k, start, split - 1);
}

int quickSelect(int arr[], int k, int n) {
    if (k < 1 || n < k) {
        return -1;
    }
    return quickSelect(arr, k - 1, 0, n - 1);
}

int main() {
    int arr[] = {8, 2, 5, 3, 9, 1, 4, 7, 10, 6};
    for (auto i = begin(arr); i != end(arr); ++i) {
        cout << *i << ' ';
    }
    cout << endl;
    for (int i=1; i<=10; ++i) {
        cout << i << "th smallest element: " << quickSelect(arr, i, 10) << endl;
    }
}

