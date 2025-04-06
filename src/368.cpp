#include "common.h"

class Solution {
  public:
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        int size = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> ans;
        vector<int> longest(size, 1), previous(size, -1);
        int longestIndex = 0;
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && longest[i] < longest[j] + 1) {
                    longest[i] = longest[j] + 1;
                    previous[i] = j;
                }
            }
            if (longest[i] > longest[longestIndex]) {
                longestIndex = i;
            }
        }

        while (longestIndex >= 0) {
            ans.push_back(nums[longestIndex]);
            longestIndex = previous[longestIndex];
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>> testSuite("Largest divisible subset", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            {1, 2},
            {1, 2, 3},
        },
        {
            {1, 2, 4, 8},
            {1, 2, 4, 8},
        },
        // My test cases
        // Submission test cases
        {
            {4, 8, 240},
            {4, 8, 10, 240},
        },
    });

    Main main;
    main.runTests(&Solution::largestDivisibleSubset, testSuite);
}
