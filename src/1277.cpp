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
    const string nameInput = "matrix";
    const string nameOutput = "squares";
    vector<TestCase<vector<vector<int>>, int>> testCases{
        {
            {nameInput, {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}}},
            {nameOutput, 15},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<vector<int>>, int> testCase) {
        Solution solution;
        return solution.countSquares(testCase.input);
    });
}
