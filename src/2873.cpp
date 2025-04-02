#include "common.h"

class Solution {
  public:
    long long maximumTripletValue(vector<int> &nums) {
        int size = nums.size();
        long long min = LLONG_MAX, max = nums[0];
        long long maxDiff = 0;
        long long ans = 0;
        vector<long long> diffs(size), maxK(size);
        maxK[size - 1] = nums[size - 1];

        // Find max diff and max k
        for (int i = 1; i < size - 1; i++) {
            maxK[size - 1 - i] = std::max(maxK[size - i], (long long)nums[size - 1 - i]);
            if (nums[i] < min) {
                min = nums[i];
                maxDiff = max - min;
            }
            if (nums[i] > max) {
                max = nums[i];
                min = LLONG_MAX;
            }
            diffs[i] = maxDiff;
        }

        for (int i = 1; i < size - 1; i++) {
            ans = std::max(ans, diffs[i] * maxK[i + 1]);
        }

        return ans > 0 ? ans : 0;
    }
};

int main() {
    TestSuite<long long, vector<int>> testSuite("Maximum triplet value", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            77,
            {12, 6, 1, 2, 7},
        },
        {
            133,
            {1, 10, 3, 4, 19},
        },
        {
            0,
            {1, 2, 3},
        },
        // Submission test cases
        {
            285,
            {6, 14, 20, 19, 19, 10, 3, 15, 12, 13, 8, 1, 2, 15, 3},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumTripletValue, testSuite);
}
