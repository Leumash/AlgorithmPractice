#include <iostream>
#include <vector>

using namespace std;

int getMaximumSubArray(const vector<int> &nums) {
    int maxSeenSoFar = 0;
    int maximum = 0;

    for (int i=0; i<nums.size(); ++i) {
        maxSeenSoFar = maxSeenSoFar + nums[i];
        if (maxSeenSoFar < 0) {
            maxSeenSoFar = 0;
        }
        if (maxSeenSoFar > maximum) {
            maximum = maxSeenSoFar;
        }
    }

    return maximum;
}

int main() {
    int num;
    vector<int> nums;

    while (cin >> num) {
        nums.push_back(num);
    }

    cout << getMaximumSubArray(nums) << endl;
}

