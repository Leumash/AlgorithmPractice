#include <iostream>
#include <cstdlib>

using namespace std;

/*
Time Complexity:
    Average Case:
        O(nlogn)
    Worst Case:
        O(n^2)
Space Complexity:
    S(n)
    For my implementation, the space complexity is S(n), however S(logn) is possible
*/

void Quicksort(int* arr, int n);
void Quicksort(int* arr, int start, int end);

int main()
{
    //int arr[] = {1,2,3,4,5,6,7,8,9,10};
    int arr[] = {5,3,1,5,3,6,8,8,1,10};
    Quicksort(arr, 10);


    for (int i=0; i<10; ++i)
    {
        cout << arr[i] <<' ';
    }

    cout << endl;
}

void Quicksort(int* arr, int n)
{
    if (n > 0)
    {
        Quicksort(arr, 0, n);
    }
}

void swap(int* arr, int left, int right)
{
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
}

void Quicksort(int* arr, int start, int end)
{
    // End Condition
    if (end - start < 2)
    {
        return;
    }

    // Pivot selection is the last piece
    int leftPos = start;
    int rightPos = end - 2;
    int pivot = end - 1;

    while (rightPos >= leftPos)
    {
        while (leftPos < end - 1 && arr[leftPos] <= arr[pivot])
        {
            ++leftPos;
        }

        while (rightPos >= start && arr[rightPos] > arr[pivot])
        {
            --rightPos;
        }

        if (rightPos > leftPos)
        {
            swap(arr, leftPos, rightPos);
            ++leftPos;
            --rightPos;
        }
    }

    swap(arr, leftPos, pivot);

    Quicksort(arr, start, leftPos);
    Quicksort(arr, leftPos + 1, end);
}

