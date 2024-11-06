#include "common.h"

class Solution {
  public:
    int maxScore(vector<vector<int>> &grid) {
        const size_t rows = grid.size();
        const size_t cols = grid[0].size();
        const size_t cells = rows * cols;
        vector<pair<int, int>> valueRows(cells);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                valueRows[i * cols + j] = {grid[i][j], i};
            }
        }
        sort(valueRows.begin(), valueRows.end());

        const int maskMax = 1 << rows;
        vector<int> dp(maskMax);
        dp[0] = 0;
        size_t l = 0, r = 0;
        while (l < cells) {
            while (r < cells && valueRows[l].first == valueRows[r].first) {
                r++;
            }
            vector<int> newDp = dp;
            for (size_t mask = 0; mask < maskMax; mask++) {
                for (size_t i = l; i < r; i++) {
                    auto [value, row] = valueRows[i];
                    if (mask & (1 << row)) {
                        continue;
                    }
                    newDp[mask | (1 << row)] = max(newDp[mask | (1 << row)], dp[mask] + value);
                }
            }
            dp = newDp;
            l = r;
        }

        return *max_element(dp.begin(), dp.end());
    }
};

int main() {
    const string nameInput = "grid";
    const string nameOutput = "max score";
    vector<TestCase<vector<vector<int>>, int>> testCases{
        // Original test cases
        {
            {nameInput, {{1, 2, 3}, {4, 3, 2}, {1, 1, 1}}},
            {nameOutput, 8},
        },
        {
            {nameInput, {{8, 7, 6}, {8, 3, 2}}},
            {nameOutput, 15},
        },
        // Submit test cases
        {
            {nameInput, {{25, 56, 56, 56, 78}, {60, 58, 56, 56, 91}, {56, 60, 46, 15, 41}, {46, 60, 77, 20, 31}, {76, 46, 24, 78, 23}, {58, 92, 17, 60, 46}, {15, 60, 20, 25, 56}, {25, 78, 15, 90, 25}, {90, 15, 25, 10, 33}}},
            {nameOutput, 666},
        },
        // My test cases
        {
            {nameInput, {{3, 3, 1}, {3, 3, 2}, {3, 3, 3}}},
            {nameOutput, 6},
        },
        {
            {nameInput, {{9, 9}, {9, 9}, {9, 9}}},
            {nameOutput, 9},
        },
        {
            {nameInput, {{1, 2}, {1, 3}}},
            {nameOutput, 5},
        },
        {
            {nameInput, {{5}, {7}, {19}, {5}}},
            {nameOutput, 31},
        },
        {
            {nameInput, {{13, 14, 14}, {14, 18, 18}, {20, 14, 20}, {20, 4, 14}}},
            {nameOutput, 65},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<vector<int>>, int> testCase) {
        Solution solution;
        return solution.maxScore(testCase.input);
    });
}
