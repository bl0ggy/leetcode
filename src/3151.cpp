#include "common.h"

class Solution {
  public:
    bool isArraySpecial(vector<int> &nums) {
        int size = nums.size();
        if (size < 2) {
            return true;
        }

        for (int i = 1; i < size; i++) {
            if (((nums[i - 1] ^ nums[i]) & 1) != 1) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    TestSuite<bool, vector<int>> testSuite("Is special array", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            {1},
        },
        {
            true,
            {2, 1, 4},
        },
        {
            false,
            {4, 3, 1, 6},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::isArraySpecial, testSuite);
}
