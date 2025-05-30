#include "common.h"

class Solution {
  public:
    int maxMoves(vector<vector<int>> &grid) {
        size_t rows = grid.size();
        size_t cols = grid[0].size();
        vector<bool> dpRow(rows, 1);

        size_t c;
        for (c = 1; c < cols; c++) {
            bool foundOne = false;
            auto tmpDpRow = dpRow;
            for (size_t r = 0; r < rows; r++) {
                bool ans = (dpRow[r] && grid[r][c - 1] < grid[r][c]);
                if (r > 0) {
                    ans |= dpRow[r - 1] && (grid[r - 1][c - 1] < grid[r][c]);
                }
                if (r + 1 < rows) {
                    ans |= dpRow[r + 1] && grid[r + 1][c - 1] < grid[r][c];
                }

                tmpDpRow[r] = ans;
                foundOne |= ans;
            }
            if (!foundOne) {
                return c - 1;
            }
            dpRow = tmpDpRow;
        }

        return c - 1;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>> testSuite("number of moves", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {{2, 4, 3, 5}, {5, 4, 9, 3}, {3, 4, 2, 11}, {10, 9, 13, 15}},
        },
        {
            0,
            {{3, 2, 4}, {2, 1, 9}, {1, 1, 7}},
        },
    });

    Main main;
    return main.runTests(&Solution::maxMoves, testSuite);
}
