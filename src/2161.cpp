#include "common.h"

class Solution {
  public:
    vector<int> pivotArray(vector<int> &nums, int pivot) {
        int size = nums.size();
        vector<int> ans(size);
        int lower = 0, equal = 0;
        for (int v : nums) {
            if (v < pivot) {
                lower++;
            } else if (v == pivot) {
                equal++;
            }
        }
        int pLower = 0, pEqual = lower, pHigher = lower + equal;
        for (int v : nums) {
            if (v < pivot) {
                ans[pLower++] = v;
            } else if (v == pivot) {
                ans[pEqual++] = v;
            } else {
                ans[pHigher++] = v;
            }
        }

        return ans;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int> testSuite("Pivot array", "nums", "pivot");
    testSuite.addTestCases({
        // Original test cases
        {
            {9, 5, 3, 10, 10, 12, 14},
            {9, 12, 5, 10, 14, 3, 10},
            10,
        },
        {
            {-3, 2, 4, 3},
            {-3, 4, 3, 2},
            2,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::pivotArray, testSuite);
}
