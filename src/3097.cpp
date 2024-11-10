#include "common.h"

class Solution {
  public:
    int minimumSubarrayLength(vector<int> &nums, int k) {
        size_t numsSize = nums.size();
        size_t minSize = INT_MAX;
        size_t start = 0, end = 0;
        vector<int> bitCounts(32, 0);
        while (end < numsSize) {
            for (int i = 0; i < 32; i++) {
                int num = nums[end];
                if ((num >> i) & 1) {
                    bitCounts[i]++;
                }
            }

            while (start <= end && bitCountsToNum(bitCounts) >= k) {
                minSize = min(minSize, end - start + 1);
                for (int i = 0; i < 32; i++) {
                    int num = nums[start];
                    if ((num >> i) & 1) {
                        bitCounts[i]--;
                    }
                }
                start++;
            }

            end++;
        }

        return minSize == INT_MAX ? -1 : minSize;
    }

    int bitCountsToNum(vector<int> &bitCounts) {
        int ret = 0;
        for (int i = 0; i < 32; i++) {
            if (bitCounts[i]) {
                ret |= 1 << i;
            }
        }
        return ret;
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
