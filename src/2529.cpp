#include "common.h"

class Solution {
  public:
    int maximumCount(vector<int> &nums) {
        int size = nums.size();
        int negatives = 0, zeros = 0;
        while (negatives < size && nums[negatives] < 0) {
            negatives++;
        }
        while (negatives + zeros < size && nums[negatives + zeros] == 0) {
            zeros++;
        }
        return max(negatives, size - negatives - zeros);
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Maximum count", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {-2, -1, -1, 1, 2, 3},
        },
        {
            3,
            {-3, -2, -1, 0, 0, 1, 2},
        },
        {
            4,
            {5, 20, 66, 1314},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumCount, testSuite);
}
