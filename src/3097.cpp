#include "common.h"

class Solution {
  public:
    int minimumSubarrayLength(vector<int> &nums, int k) {
        size_t numsSize = nums.size();
        int minSize = INT_MAX;
        int numOr;
        for (int i = 0; i < numsSize; i++) {
            numOr = 0;
            for (int j = i; j < numsSize; j++) {
                if ((numOr |= nums[j]) >= k) {
                    minSize = min(minSize, j - i + 1);
                }
            }
        }

        return minSize == INT_MAX ? -1 : minSize;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("shortest subarray with OR ar least K II", "values", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            1,
            {1, 2, 3},
            2,
        },
        {
            3,
            {2, 1, 8},
            10,
        },
        {
            1,
            {1, 2},
            0,
        },
    });

    Main main;
    main.runTests(&Solution::minimumSubarrayLength, testSuite);
}
