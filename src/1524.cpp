#include "common.h"

class Solution {
  public:
    int numOfSubarrays(vector<int> &arr) {
        const int mod = 1000000007;
        int size = arr.size();
        vector<int> dp(size + 1, 0);
        int countEven = 0, countOdd = 0, countTotal = 0;
        for (int col = 0; col < size; col++) {
            dp[col + 1] = dp[col] + arr[col];
            if (dp[col + 1] & 1) {
                countOdd++;
                countTotal += 1 + countEven;
            } else {
                countEven++;
                countTotal += countOdd;
            }
            countTotal = countTotal % mod;
        }
        return countTotal;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Num of subarrays", "arr");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {1, 3, 5},
        },
        {
            0,
            {2, 4, 6},
        },
        {
            16,
            {1, 2, 3, 4, 5, 6, 7},
        },
        // Submission test cases
        // My test cases
        {
            4,
            {1, 2, 3},
        },
    });

    Main main;
    main.runTests(&Solution::numOfSubarrays, testSuite);
}
