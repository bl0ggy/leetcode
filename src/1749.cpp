#include "common.h"

class Solution {
  public:
    int maxAbsoluteSum(vector<int> &nums) {
        int size = nums.size();
        int currentSumMax = nums[0];
        int currentSumMin = nums[0];
        int maxSum = abs(currentSumMax);
        int minSum = abs(currentSumMin);
        int pointer = 1;

        while (pointer < size) {
            currentSumMax = max(nums[pointer], currentSumMax + nums[pointer]);
            maxSum = max(maxSum, currentSumMax);
            currentSumMin = min(nums[pointer], currentSumMin + nums[pointer]);
            minSum = min(minSum, currentSumMin);
            pointer++;
        }

        return max(maxSum, abs(minSum));
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Max absolute sum", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {1, -3, 2, 3, -4},
        },
        {
            8,
            {2, -5, 1, -4, 3, -2},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maxAbsoluteSum, testSuite);
}
