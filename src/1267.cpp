#include "common.h"

class Solution {
  public:
    int countServers(vector<vector<int>> &grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<int> rowCounts(rows, 0), colCounts(cols, 0);
        int ans = 0;

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (grid[row][col]) {
                    rowCounts[row]++;
                    colCounts[col]++;
                }
            }
        }

        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (grid[row][col] && (rowCounts[row] > 1 || colCounts[col] > 1)) {
                    ans++;
                }
            }
        }

        return ans;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>> testSuite("Communicating servers", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            0,
            {{1, 0}, {0, 1}},
        },
        {
            3,
            {{1, 0}, {1, 1}},
        },
        {
            4,
            {
                {1, 1, 0, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1},
            },
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countServers, testSuite);
}
