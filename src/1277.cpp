#include "common.h"

class Solution {
  public:
    int countSquares(vector<vector<int>> &matrix) {
        int matrixRows = matrix.size();
        int matrixCols = matrix[0].size();
        int count = 0;
        vector<vector<int>> dp(matrixRows + 1, vector<int>(matrixCols + 1, 0));

        for (int mRow = 0; mRow < matrixRows; mRow++) {
            for (int mCol = 0; mCol < matrixCols; mCol++) {
                if (matrix[mRow][mCol] == 1) {
                    dp[mRow + 1][mCol + 1] = min({dp[mRow][mCol + 1], dp[mRow + 1][mCol], dp[mRow][mCol]}) + 1;
                    count += dp[mRow + 1][mCol + 1];
                }
            }
        }

        return count;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>> testSuite("squares", "matrix");
    testSuite.addTestCases({
        // Original test cases
        {
            15,
            {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}},
        },
        {
            7,
            {{1, 0, 1}, {1, 1, 0}, {1, 1, 0}},
        },
    });

    Main main;
    return main.runTests(&Solution::countSquares, testSuite);
}
