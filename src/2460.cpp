#include "common.h"

class Solution {
  public:
    vector<int> applyOperations(vector<int> &nums) {
        int size = nums.size();

        for (int i = 0; i < size - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                nums[i] *= 2;
                nums[i + 1] = 0;
            }
        }

        int zero = 0;
        for (int i = 0; i < size; i++) {
            if (nums[i] != 0) {
                nums[zero++] = nums[i];
            }
        }
        while (zero < size) {
            nums[zero++] = 0;
        }

        return nums;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>> testSuite("Applied operations", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            {1, 4, 2, 0, 0, 0},
            {1, 2, 2, 1, 1, 0},
        },
        {
            {1, 0},
            {0, 1},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::applyOperations, testSuite);
}
