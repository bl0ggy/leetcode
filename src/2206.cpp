#include "common.h"

class Solution {
  public:
    bool divideArray(vector<int> &nums) {
        int size = nums.size();
        unordered_map<int, int> count;
        for (int i = 0; i < size; i++) {
            count[nums[i]]++;
        }
        for (auto [_, c] : count) {
            if ((c % 2) != 0) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    TestSuite<bool, vector<int>> testSuite("Is array of pairs", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            {3, 2, 3, 2, 2, 2},
        },
        {
            false,
            {1, 2, 3, 4},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::divideArray, testSuite);
}
