#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <time.h>

using namespace std;

vector<int> GetRandomSet(int min, int max, int cardinality)
{
    srand(time(NULL));
    vector<int> toReturn;

    for (int i=0; i<cardinality; ++i)
    {
        int num = rand() % (max + 1 - min);

        num += min;
        toReturn.push_back(num);
    }

    return toReturn;
}

void PrintSet(const vector<int> &S)
{
    for (int i=0; i<S.size(); ++i)
    {
        cout << S[i] << ' ';
    }

    cout << endl;
}

multiset<int> GetSubSet(unordered_map<int,int> &containerToPrevious)
{
    multiset<int> toReturn;

    int current = 0;

    int toAdd = current - containerToPrevious[0];

    toReturn.insert(toAdd);

    while (true)
    {
        current = containerToPrevious[current];

        toAdd = current - containerToPrevious[current];

        toReturn.insert(toAdd);

        if (containerToPrevious[current] == 0)
        {
            break;
        }

    }

    return toReturn;
}

void SubsetSum(const vector<int> &S)
{
    unordered_map<int,int> containerToPrevious;

    for (int i=0; i<S.size(); ++i)
    {
        if (S[i] == 0)
        {
            continue;
        }

        vector< pair<int,int> > toAdd;

        toAdd.push_back(make_pair(S[i], 0));

        for (auto mit = containerToPrevious.begin(); mit != containerToPrevious.end(); ++mit)
        {
            toAdd.push_back(make_pair(mit->first + S[i], mit->first));
        }

        for (int i=0; i<toAdd.size(); ++i)
        {
            if (containerToPrevious.count(toAdd[i].first) == 0)
            {
                containerToPrevious[toAdd[i].first] = toAdd[i].second;
            }
        }
    }

    if (containerToPrevious.count(0) == 0)
    {
        cout << "There is no solution" << endl;
    }
    else
    {
        multiset<int> solution = GetSubSet(containerToPrevious);

        cout << "Set S': ";

        for (auto sit = solution.begin(); sit != solution.end(); ++sit)
        {
            cout << *sit << ' ';
        }

        cout << endl;
    }
}

int main()
{
    int min = -100;
    int max = 100;
    int cardinality = 10;

    vector<int> S = GetRandomSet(min, max, cardinality);

    cout << "Set S: ";
    PrintSet(S);
    cout << "Cardinality: " << cardinality << endl << endl;

    SubsetSum(S);

    return 0;
}
