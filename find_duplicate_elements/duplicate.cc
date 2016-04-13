// Given an array with N elements (numbers from 0 to N-1). Find all duplicate elements.

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> GetDuplicateElements(const vector<int> &arr)
{
    unordered_set<int> duplicates;
    unordered_set<int> seen;

    for (int num : arr)
    {
        if (seen.count(num) > 0)
        {
            duplicates.insert(num);
        }

        seen.insert(num);
    }

    return vector<int>(duplicates.begin(), duplicates.end());
}

int main()
{
    return 0;
}

