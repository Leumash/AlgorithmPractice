/*
In computer science, the maximum subarray problem is the task of finding the contiguous subarray within a one-dimensional array of numbers which has the largest sum. For example, for the sequence of values −2, 1, −3, 4, −1, 2, 1, −5, 4; the contiguous subarray with the largest sum is 4, −1, 2, 1, with sum 6.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int GetSumOfMaximumSubarray(const vector<int> &arr)
{
    int maximum = *max_element(arr.begin(), arr.end());

    if (maximum < 0)
    {
        return maximum;
    }

    int maxUpTo = 0;
    int overallMax = 0;

    for (const int num : arr)
    {
        maxUpTo = max(0, maxUpTo + num);
        overallMax = max(overallMax, maxUpTo);
    }

    return overallMax;
}

int main()
{
    int T;
    int N;

    cin >> T;

    for (int i=0; i<T; ++i)
    {
        cin >> N;
        vector<int> arr(N);

        for (int j=0; j<N; ++j)
        {
            cin >> arr[j];
        }

        cout << GetSumOfMaximumSubarray(arr) << endl;
    }

    return 0;
}

