#include "common.h"

class Solution {
  public:
    bool canSortArray(vector<int> &nums) {
        // Algorithm:
        // [4,5,8] is sortable (already sorted)
        // but [8,5,4] is not sortable, even though we can swap 8 and 4
        // but since they're separated by a different set bit number
        // we can browse by block of set bits and make sure that when the
        // number of set bits change, we check that the num is higher than
        // the highest num of the previous set bits
        uint currentSetBits = 0;
        uint currentSetBitsBiggestNum = 0;
        uint lastSetBitsBiggestNum = 0;
        for (uint num : nums) {
            int count = popcount(num);
            if (count == currentSetBits) {
                currentSetBitsBiggestNum = max(currentSetBitsBiggestNum, num);
            } else {
                currentSetBits = count;
                lastSetBitsBiggestNum = currentSetBitsBiggestNum;
            }
            currentSetBitsBiggestNum = max(currentSetBitsBiggestNum, num);
            if (lastSetBitsBiggestNum > num) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    const string nameInput = "values";
    const string nameOutput = "can sort array";
    vector<TestCase<vector<int>, bool>> testCases{
        // Original test cases
        {
            {nameInput, {8, 4, 2, 30, 15}},
            {nameOutput, true},
        },
        {
            {nameInput, {1, 2, 3, 4, 5}},
            {nameOutput, true},
        },
        {
            {nameInput, {3, 16, 8, 4, 2}},
            {nameOutput, false},
        },
        // My test cases
        {
            {nameInput, {4, 5, 8}}, // Already sorted non-adjacent 1-2-1 set bits
            {nameOutput, true},
        },
        {
            {nameInput, {8, 5, 4}}, // Non sorted non-adjacent 1-2-1 set bits
            {nameOutput, false},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<int>, bool> testCase) {
        Solution solution;
        return solution.canSortArray(testCase.input);
    });
}
