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
    TestSuite<int, vector<int>> testSuite("longest square streak", "values");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {4, 3, 6, 16, 8, 2},
        },
        {
            -1,
            {2, 3, 5, 6, 7},
        },
        // My test cases
        {
            -1,
            {2, 3},
        },
        {
            -1,
            {4, 5},
        },
        {
            -1,
            {2},
        },
        {
            4,
            {3, 9, 81, 6561},
        },
    });

    Main main;
    return main.runTests(&Solution::longestSquareStreak, testSuite);
}
