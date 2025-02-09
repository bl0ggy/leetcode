#include "common.h"

class Solution {
  public:
    long long countBadPairs(vector<int> &nums) {
        long long size = nums.size();
        vector<int> diffs(size);
        unordered_map<int, long long> count;
        long long sum = 0;
        for (int i = 0; i < size; i++) {
            count[nums[i] - i]++;
        }

        long long numberOfPairs = size * (size - 1) / 2;
        for (auto [k, v] : count) {
            if (v > 1) {
                sum += (v) * (v - 1) / 2;
            }
        }

        return numberOfPairs - sum;
    }
};

int main() {
    TestSuite<long long, vector<int>> testSuite("Bad pairs", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {4, 1, 3, 3},
        },
        {
            0,
            {1, 2, 3, 4, 5},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countBadPairs, testSuite);
}
