#include "common.h"

class Solution {
  public:
    int subsetXORSum(vector<int> &nums) {
        int size = nums.size();
        if (size == 0) {
            return 0;
        } else if (size == 1) {
            return nums[0];
        }

        return recurse(nums, 0, 0);
    }

    int recurse(vector<int> &nums, int index, int currentXor) {
        if (index >= nums.size()) {
            return currentXor;
        }

        return recurse(nums, index + 1, currentXor) + recurse(nums, index + 1, currentXor xor nums[index]);
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Subset XOR sum", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            6,
            {1, 3},
        },
        {
            28,
            {5, 1, 6},
        },
        {
            480,
            {3, 4, 5, 6, 7, 8},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::subsetXORSum, testSuite);
}
