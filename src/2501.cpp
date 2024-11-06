#include "common.h"

class Solution {
  public:
    int longestSquareStreak(vector<int> &nums) {
        // Longest streak: 2, 4, 8, 16, 256, 65536 -> 6
        // Square root of maximum value 10e5 is 316.2, so a streak require the value to be under 317
        unordered_set<int> unique(nums.begin(), nums.end());
        nums = vector<int>(unique.begin(), unique.end());
        sort(nums.begin(), nums.end());
        int maxCount = 0;
        auto globalNum = nums.begin();
        auto numsEnd = nums.end();
        unique.clear(); // Reuse to skip already processed values
        while (globalNum != numsEnd && *globalNum < 317) {
            auto num = globalNum;
            if (unique.count(*num)) {
                globalNum++;
                continue;
            }
            int count = 1;
            while (*num < 317 && (num = find(num + 1, numsEnd, (*num) * (*num))) != numsEnd) {
                count++;
            }
            maxCount = max(maxCount, count);
            if (maxCount == 6) { // Longest streak
                return 6;
            }
            globalNum++;
        }

        return maxCount <= 1 ? -1 : maxCount;
    }
};

int main() {
    const string nameInput = "values";
    const string nameOutput = "longest square streak";
    vector<TestCase<vector<int>, int>> testCases{
        // Original test cases
        {
            {nameInput, {4, 3, 6, 16, 8, 2}},
            {nameOutput, 3},
        },
        {
            {nameInput, {2, 3, 5, 6, 7}},
            {nameOutput, -1},
        },
        // My test cases
        {
            {nameInput, {2, 3}},
            {nameOutput, -1},
        },
        {
            {nameInput, {4, 5}},
            {nameOutput, -1},
        },
        {
            {nameInput, {2}},
            {nameOutput, -1},
        },
        {
            {nameInput, {3, 9, 81, 6561}},
            {nameOutput, 4},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<int>, int> testCase) {
        Solution solution;
        return solution.longestSquareStreak(testCase.input);
    });
}
