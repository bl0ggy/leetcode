#include "common.h"

class Solution {
  public:
    // Same as 2873, O(n)
    long long maximumTripletValue(vector<int> &nums) {
        long long ans = 0, maxDiff = 0, maxNum = nums[0];
        int size = nums.size();

        for (int i = 1; i < size - 1; i++) {
            maxDiff = max(maxDiff, maxNum - nums[i]);
            maxNum = max(maxNum, (long long)nums[i]);
            ans = max(ans, maxDiff * nums[i + 1]);
        }

        return ans > 0 ? ans : 0;
    }
};

int main() {
    TestSuite<long long, vector<int>> testSuite("Maximum triplet vaule", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            77,
            {12, 6, 1, 2, 7},
        },
        {
            133,
            {1, 10, 3, 4, 19},
        },
        {
            0,
            {1, 2, 3},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumTripletValue, testSuite);
}
