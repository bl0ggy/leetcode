#include "common.h"

class Solution {
  public:
    int maxAscendingSum(vector<int> &nums) {
        int size = nums.size();
        if (size < 2) {
            return nums[0];
        }
        int sum = nums[0];
        int ans = nums[0];
        for (int i = 1; i < size; i++) {
            int diff = nums[i] - nums[i - 1];
            if (diff > 0) {
                sum += nums[i];
            } else {
                sum = nums[i];
            }
            ans = max(ans, sum);
        }

        return ans;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Max ascending sum", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            65,
            {10, 20, 30, 5, 10, 50},
        },
        {
            150,
            {10, 20, 30, 40, 50},
        },
        {
            33,
            {12, 17, 15, 13, 10, 11, 12},
        },
        // Submission test cases
        // My test cases
        {
            3,
            {3, 3, 2},
        },
    });

    Main main;
    main.runTests(&Solution::maxAscendingSum, testSuite);
}
