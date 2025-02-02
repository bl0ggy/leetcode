#include "common.h"

class Solution {
  public:
    bool check(vector<int> &nums) {
        int size = nums.size();
        bool foundLower = false;
        for (int i = 1; i < size; i++) {
            if (nums[i - 1] > nums[i]) {
                if (foundLower) {
                    return false;
                }
                foundLower = true;
            }
        }

        return !foundLower || nums[0] >= nums[size - 1];
    }
};

int main() {
    TestSuite<bool, vector<int>> testSuite("Is sorted and rotated", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            {3, 4, 5, 1, 2},
        },
        {
            false,
            {2, 1, 3, 4},
        },
        {
            true,
            {1, 2, 3},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::check, testSuite);
}
