#include "common.h"

class Solution {
  public:
    int maxSubArray(vector<int> &nums) {
        int size = nums.size();
        int maxSum = nums[0], answer = nums[0];

        for (int i = 1; i < size; i++) {
            maxSum = max(nums[i], maxSum + nums[i]);
            answer = max(answer, maxSum);
        }

        return answer;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("53", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            6,
            {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        },
        {
            1,
            {1},
        },
        {
            23,
            {5, 4, -1, 7, 8},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maxSubArray, testSuite);
}
