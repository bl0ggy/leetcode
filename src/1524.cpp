#include "common.h"

class Solution {
  public:
    // Memory limit exceeded
    // and probably Time limit exceeded too
    int numOfSubarrays(vector<int> &arr) {
        const int mod = 1000000007;
        int size = arr.size();
        vector<vector<int>> dp(size + 1, vector<int>(size + 2, 0));
        // 1 2 3
        // 1     = odd
        // 1 2   = odd
        // 1 2 3 = even
        // 2     = even
        // 2 3   = odd
        // 3     = odd
        // [0 1 3 6 0]
        // [0 0 2 5 0]
        // [0 0 0 3 0]

        int count = 0;
        for (int col = 0; col < size; col++) {
            dp[0][col + 1] = dp[0][col] + arr[col];
            if ((dp[0][col + 1] & 1)) {
                count++;
                if (count > mod) {
                    count -= mod;
                }
            }
        }
        for (int row = 1; row < size + 1; row++) {
            for (int col = row; col < size + 1; col++) {
                dp[row][col] = dp[row - 1][col] - dp[row - 1][row];
                if ((dp[row][col] & 1)) {
                    count++;
                    if (count > mod) {
                        count -= mod;
                    }
                }
            }
        }
        return count;
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
