#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <time.h>

using namespace std;

vector<int> GenerateRandomSet(int count, int min, int max)
{
    srand(time(NULL));

    vector<int> toReturn(count);

    for (int i=0; i<count; ++i)
    {
        toReturn[i] = (rand() % (max - min)) + min;
    }

    return toReturn;
}

vector<int> GetSubsetSum(int targetSum, const unordered_map<int,int> &totalToParent)
{
    vector<int> subsetSum;

    subsetSum.push_back(targetSum - totalToParent.at(targetSum));

    for (int currentTotal = totalToParent.at(targetSum); currentTotal != 0; currentTotal = totalToParent.at(currentTotal))
    {
        int element = currentTotal - totalToParent.at(currentTotal);

        subsetSum.push_back(element);
    }

    return subsetSum;
}

bool SubsetSum(const vector<int> &S, int targetSum, vector<int> &subsetSum)
{
    unordered_map<int,int> totalToParent;

    for (int element : S)
    {
        if (element == 0)
        {
            continue;
        }

        vector<pair<int,int>> toAdd;

        toAdd.push_back(make_pair(element, 0));

        for (const auto &tTP : totalToParent)
        {
            int currentTotal = tTP.first;

            toAdd.push_back(make_pair(currentTotal + element, currentTotal));
        }

        for (const auto &tA : toAdd)
        {
            if (totalToParent.count(tA.first) == 0)
            {
                totalToParent[tA.first] = tA.second;
            }
        }
    }

    if (totalToParent.count(targetSum) > 0)
    {
        subsetSum = GetSubsetSum(targetSum, totalToParent);

        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int targetSum = 0;
    vector<int> S = GenerateRandomSet(10, -10, 11);

    cout << "Set S: ";

    for (int element : S)
    {
        cout << element << ' ';
    }

    cout << endl;
    cout << "Cardinality: " << S.size() << endl;

    cout << "Target Sum: " << targetSum << endl;

    vector<int> subsetSum;

    if (SubsetSum(S, targetSum, subsetSum))
    {
        cout << "Subset Sum: ";

        for (int element : subsetSum)
        {
            cout << element << ' ';
        }

        cout << endl;
    }
    else
    {
        cout << "The subset sum does not exist." << endl;
    }

    return 0;
}

