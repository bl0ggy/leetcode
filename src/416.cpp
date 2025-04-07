#include "common.h"
#include <numeric>

class Solution {
  public:
    bool canPartition(vector<int> &nums) {
        int size = nums.size();
        if (size == 1) {
            return false;
        }

        int sum = reduce(nums.begin(), nums.end());
        if (sum % 2 != 0) {
            return false;
        }

        int half = sum / 2;
        bitset<10001> bits{1};
        for (auto n : nums) {
            bits |= bits << n; // For every previous possible sums, add "n" as a possible sum
        }

        return bits[half];
    }
};

int main() {
    TestSuite<bool, vector<int>> testSuite("416", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            {1, 5, 11, 5},
        },
        {
            false,
            {1, 2, 3, 5},
        },
        // My test cases
        {
            true,
            {50, 40, 30, 30, 30},
        },
        {
            true,
            {50, 30, 20, 1, 1},
        },
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::canPartition, testSuite);
}
