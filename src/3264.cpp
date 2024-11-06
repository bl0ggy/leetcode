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
    const string nameInput1 = "values";
    const string nameInput2 = "k";
    const string nameInput3 = "multiplier";
    const string nameOutput = "final state";
    vector<TestCase<vector<int>, int, int, vector<int>>> testCases{
        // Original test cases
        {
            {nameInput1, {2, 1, 3, 5, 6}},
            {nameInput2, 5},
            {nameInput3, 2},
            {nameOutput, {8, 4, 6, 5, 6}},
        },
        {
            {nameInput1, {1, 2}},
            {nameInput2, 3},
            {nameInput3, 4},
            {nameOutput, {16, 8}},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<int>, int, int, vector<int>> testCase) {
        Solution solution;
        return solution.getFinalState(testCase.input1, testCase.input2, testCase.input3);
    });
}
