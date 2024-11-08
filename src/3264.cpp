#include "common.h"

class Solution {
  public:
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier) {
        for (int i = 0; i < k; i++) {
            auto it = min_element(nums.begin(), nums.end());
            *it = *it * multiplier;
        }

        return nums;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int, int> testSuite("final state", "values", "k", "multiplier");
    testSuite.addTestCases({
        // Original test cases
        {
            {8, 4, 6, 5, 6},
            {2, 1, 3, 5, 6},
            5,
            2,
        },
        {
            {16, 8},
            {1, 2},
            3,
            4,
        },
    });

    Main main;
    return main.runTests(&Solution::getFinalState, testSuite);
}
