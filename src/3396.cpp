#include "common.h"

class Solution {
  public:
    int minimumOperations(vector<int> &nums) {
        int size = nums.size();
        array<int, 101> hash{};
        int actionCount = 0;
        int left = 0;
        for (int right = 0; right < size; right++) {
            int n = nums[right];
            hash[n]++;
            if (left > right) {
                continue;
            }

            while (hash[n] == 2) {
                actionCount++;
                hash[nums[left++]]--;
                if (left < size) {
                    hash[nums[left++]]--;
                }
                if (left < size) {
                    hash[nums[left++]]--;
                }
            }
        }

        return actionCount;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("3396", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {1, 2, 3, 4, 2, 3, 3, 5, 7},
        },
        {
            2,
            {4, 5, 6, 4, 4},
        },
        {
            0,
            {6, 7, 8, 9},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minimumOperations, testSuite);
}
