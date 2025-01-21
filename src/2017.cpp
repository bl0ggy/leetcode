#include "common.h"
#include <numeric>

class Solution {
  public:
    long long gridGame(vector<vector<int>> &grid) {
        long long ans = LONG_LONG_MAX;
        int cols = grid[0].size();
        vector<vector<long long>> dp(cols, vector<long long>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = accumulate(grid[0].begin() + 1, grid[0].end(), 0LL);
        ans = min(ans, max(dp[0][0], dp[0][1]));

        for (int i = 1; i < cols; i++) {
            dp[i][0] = dp[i - 1][0] + grid[1][i - 1];
            dp[i][1] = dp[i - 1][1] - grid[0][i];
            ans = min(ans, max(dp[i][0], dp[i][1]));
        }

        return ans;
    }
};

int main() {
    TestSuite<long long, vector<vector<int>>> testSuite("Points", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {{2, 5, 4}, {1, 5, 1}},
        },
        {
            4,
            {{3, 3, 1}, {8, 5, 2}},
        },
        {
            7,
            {{1, 3, 1, 15}, {1, 3, 3, 1}},
        },
        // Submission test cases
        {
            63,
            {{20, 3, 20, 17, 2, 12, 15, 17, 4, 15}, {20, 10, 13, 14, 15, 5, 2, 3, 14, 3}},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::gridGame, testSuite);
}
