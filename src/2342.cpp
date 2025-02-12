#include "common.h"

class Solution {
  public:
    int maximumSum(vector<int> &nums) {
        int size = nums.size();
        vector<pair<int, int>> digitsSums(82, {0, 0}); // Max sum of digits for 10e9 is 9*9=81

        for (int i = 0; i < size; i++) {
            int n = nums[i];
            int sum = 0;
            while (n > 0) {
                sum += n % 10;
                n /= 10;
            }
            n = nums[i];
            if (n > digitsSums[sum].first) {
                digitsSums[sum].second = digitsSums[sum].first;
                digitsSums[sum].first = n;
            } else if (n > digitsSums[sum].second) {
                digitsSums[sum].second = n;
            }
        }

        int maxSum = -1;
        for (auto [first, second] : digitsSums) {
            if (second > 0) {
                maxSum = max(maxSum, first + second);
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
        {
            973,
            {229, 398, 269, 317, 420, 464, 491, 218, 439, 153, 482, 169, 411, 93, 147, 50, 347, 210, 251, 366, 401},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumSum, testSuite);
}
