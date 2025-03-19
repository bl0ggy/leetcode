#include "common.h"

class Solution {
  public:
    int minOperations(vector<int> &nums) {
        int size = nums.size();
        int minOperations = 0;
        for (int i = 0; i < size; i++) {
            if (nums[i] == 0) {
                if (i >= size - 2) {
                    return -1;
                }
                minOperations++;
                nums[i] = nums[i] == 0 ? 1 : 0;
                nums[i + 1] = nums[i + 1] == 0 ? 1 : 0;
                nums[i + 2] = nums[i + 2] == 0 ? 1 : 0;
            }
        }

        return minOperations;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Min operations", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {0, 1, 1, 1, 0, 0},
        },
        {
            -1,
            {0, 1, 1, 1},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minOperations, testSuite);
}
