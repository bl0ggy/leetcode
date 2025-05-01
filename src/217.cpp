#include "common.h"

class Solution {
  public:
    bool containsDuplicate(vector<int> &nums) {
        int size = nums.size();
        sort(nums.begin(), nums.end());
        for (int i = 1; i < size; i++) {
            if (nums[i - 1] == nums[i]) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    TestSuite<bool, vector<int>> testSuite("217", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            {1, 2, 3, 1},
        },
        {
            false,
            {1, 2, 3, 4},
        },
        {
            true,
            {1, 1, 1, 3, 3, 4, 3, 2, 4, 2},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::containsDuplicate, testSuite);
}
