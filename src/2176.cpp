#include "common.h"

class Solution {
  public:
    int countPairs(vector<int> &nums, int k) {
        int size = nums.size();
        int count = 0;

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (nums[i] == nums[j] && ((i * j) % k) == 0) {
                    count++;
                }
            }
        }

        return count;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("2176", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {3, 1, 2, 2, 2, 1, 3},
            2,
        },
        {
            0,
            {1, 2, 3, 4},
            1,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countPairs, testSuite);
}
