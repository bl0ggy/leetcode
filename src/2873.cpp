#include "common.h"

class Solution {
  public:
    long long maximumTripletValue(vector<int> &nums) {
        int size = nums.size();
        long long ans = 0;
        int maxNum = nums[0], maxDiff = 0;

        // Find max diff and max k
        for (int i = 1; i < size - 1; i++) {
            maxDiff = max(maxDiff, maxNum - nums[i]);
            ans = max(ans, (long long)maxDiff * nums[i + 1]);
            maxNum = max(maxNum, nums[i]);
        }

        return ans > 0 ? ans : 0;
    }
};

int main() {
    TestSuite<long long, vector<int>> testSuite("Maximum triplet value", "nums");
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
        {
            285,
            {6, 14, 20, 19, 19, 10, 3, 15, 12, 13, 8, 1, 2, 15, 3},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumTripletValue, testSuite);
}
