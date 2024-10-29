#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

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
    vector<vector<int>> input{{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};
    int expectedCount = 15;

    auto start = chrono::system_clock::now();

    Solution solution;
    int count = solution.countSquares(input);

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "elapsed = " << elapsed.count() << "ms\n";
    cout << "count=" << count << "\n";
    assert(count == expectedCount);
}
