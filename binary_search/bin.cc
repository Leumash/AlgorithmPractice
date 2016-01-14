#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

void PrintArr(int* arr, int n);
void FillArr(int* arr, int n);
// Returns the index of found value, if not found, returns -1
int BinarySearch(int* arr, int n, int k);

int main()
{
    int n = 10;
    int arr[n];
    FillArr(arr, n);
    PrintArr(arr, n);
    cout << BinarySearch(arr, n, 10);
    return 0;
}

void PrintArr(int* arr, int n)
{
    for (int i=0; i<n; ++i)
    {
        cout << arr[i] <<' ';
    }

    cout << endl;
}

void FillArr(int* arr, int n)
{
    srand(time(NULL));

    int fill = 0;

    for (int i=0; i<n; ++i)
    {
        fill += rand() % 5;
        arr[i] = fill;
    }
}

int BinarySearch(int* arr, int start, int end, int target)
{
    int middle = (end - start)/2 + start;

    if (start == end)
    {
        return -1;
    }

    if (arr[middle] == target)
    {
        return middle;
    }

    if (target < arr[middle])
    {
        return BinarySearch(arr, start, middle, target);
    }

    return BinarySearch(arr, middle + 1, end, target);
}

int BinarySearch(int* arr, int n, int k)
{
    // Validate Input
    if (n <= 0)     // Invalid array
    {
        return -1;
    }

    // Check if sorted?
    // Meh();

    // Perform search
    // Recursive Implementation
    return BinarySearch(arr, 0, n, k);
}

