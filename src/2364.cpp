#include "common.h"

class Solution {
  public:
    // Time limit exceeded
    long long countBadPairs(vector<int> &nums) {
        int size = nums.size();
        long long sum = 0;
        for (int j = 1; j < size; j++) {
            for (int i = 0; i < j; i++) {
                if (j - i != nums[j] - nums[i]) {
                    sum++;
                }
            }
        }

        return sum;
    }
};

int main() {
    TestSuite<long long, vector<int>> testSuite("Bad pairs", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {4, 1, 3, 3},
        },
        {
            0,
            {1, 2, 3, 4, 5},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countBadPairs, testSuite);
}
