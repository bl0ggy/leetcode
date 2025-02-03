#include "common.h"

class Solution {
  public:
    int longestMonotonicSubarray(vector<int> &nums) {
        int size = nums.size();
        if (size < 2) {
            return 1;
        }
        int direction = nums[1] - nums[0];
        int sum = 1;
        int ans = 1;
        for (int i = 1; i < size; i++) {
            int diff = nums[i] - nums[i - 1];
            if ((diff < 0 && direction < 0) || (diff > 0 && direction > 0)) {
                sum++;
            } else {
                direction = diff;
                sum = diff == 0 ? 1 : 2;
            }
            ans = max(ans, sum);
        }

        return ans;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Longest monotonic subarray", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {1, 4, 3, 3, 2},
        },
        {
            1,
            {3, 3, 3, 3},
        },
        {
            3,
            {3, 2, 1},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::longestMonotonicSubarray, testSuite);
}
