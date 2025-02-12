#include "common.h"

class Solution {
  public:
    // Quite slow
    int maximumSum(vector<int> &nums) {
        int size = nums.size();
        unordered_map<int, list<int>> digitsSums;

        for (int i = 0; i < size; i++) {
            int n = nums[i];
            int sum = 0;
            int factor = 1000000000;
            while (n > 0) {
                int digit = n / factor;
                sum += n / factor;
                n -= digit * factor;
                factor /= 10;
            }
            digitsSums[sum].push_back(nums[i]);
        }

        int maxSum = -1;
        for (auto [key, value] : digitsSums) {
            if (value.size() >= 2) {
                value.sort(greater<int>());
                maxSum = max(maxSum, (*value.begin()) + (*(next(value.begin()))));
            }
        }

        return maxSum;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Max sum", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            54,
            {18, 43, 36, 13, 7},
        },
        {
            -1,
            {10, 12, 19, 14},
        },
        // Submission test cases
        {
            12,
            {4, 6, 10, 6},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumSum, testSuite);
}
