#include "common.h"

class Solution {
  public:
    vector<int> getMaximumXor(vector<int> &nums, int maximumBit) {
        int maxNum = (~(0) xor (1 << 31)) >> (31 - maximumBit);
        size_t numsSize = nums.size();
        vector<int> xors(numsSize, 0);
        xors[numsSize - 1] = nums[0];

        for (size_t i = 1; i < numsSize; i++) {
            xors[numsSize - i - 1] = nums[i] xor xors[numsSize - i];
        }

        for (auto &x : xors) {
            x = x xor ((x xor (~x)) & maxNum);
        }

        return xors;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int> testSuite("maximum xor", "values", "maximum bit");
    testSuite.addTestCases({
        // Original test cases
        {
            {0, 3, 2, 3},
            {0, 1, 1, 3},
            2,
        },
        {
            {5, 2, 6, 5},
            {2, 3, 4, 7},
            3,
        },
        {
            {4, 3, 6, 4, 6, 7},
            {0, 1, 2, 2, 5, 7},
            3,
        },
    });

    Main main;
    return main.runTests(&Solution::getMaximumXor, testSuite);
}
