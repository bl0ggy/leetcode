#include "common.h"

class Solution {
  public:
    int countMatchingSubarrays(vector<int> &nums, vector<int> &pattern) {
        int nSize = nums.size();
        int pSize = pattern.size();
        int npSize = nSize - 1;
        vector<int> nPattern(npSize);
        for (int i = 0; i < npSize; i++) {
            int a = nums[i], b = nums[i + 1];
            nPattern[i] = (a > b) * (-1) + (a < b);
        }

        int left = 1, right = 1;
        vector<int> npPattern;
        npPattern.insert(npPattern.begin(), pattern.begin(), pattern.end());
        npPattern.insert(npPattern.end(), nPattern.begin(), nPattern.end());
        int npPatternSize = npPattern.size();
        vector<int> z(npPatternSize);
        int result = 0;
        for (int i = 1; i < npPatternSize; i++) {
            if (i < right) {
                z[i] = min(right - i, z[i - left]);
            }
            while (i + z[i] < npPatternSize && npPattern[i + z[i]] == npPattern[z[i]]) {
                z[i]++;
            }
            if (i + z[i] > right) {
                left = i;
                right = i + z[i];
            }
            if (z[i] >= pSize && i >= pSize) {
                result++;
            }
        }

        return result;
    }
};

int main() {
    TestSuite<int, vector<int>, vector<int>> testSuite("Matching subarrays", "nums", "pattern");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {1, 2, 3, 4, 5, 6},
            {1, 1},
        },
        {
            2,
            {1, 4, 4, 1, 3, 5, 5, 3},
            {1, 0, -1},
        },
        // Submission test cases
        {
            1,
            {350719501, 350719501, 350719501, 233017710, 21467383}, // {0, 0, -1, -1}
            {0, -1},
        },
        {
            2,
            {3759873, 3759873, 108284197, 3759873, 108284197, 108284197, 145379806, 108284197, 145379806, 177967660, 177967660},
            {1, -1, 1},
        },
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::countMatchingSubarrays, testSuite);
}
