#include "common.h"

class Solution {
  public:
    int minOperations(vector<vector<int>> &grid, int x) {
        int height = grid.size();
        int width = grid[0].size();
        int cells = height * width;
        vector<int> actions(cells);
        int sumOfActions = 0;

        vector<int> allElements(height * width);
        for (int row = 0; row < height; row++) {
            int r = width * row;
            for (int col = 0; col < width; col++) {
                allElements[r + col] = grid[row][col];
            }
        }
        sort(allElements.begin(), allElements.end());
        int start = allElements[(cells - 1) / 2];
        for (int i = 0; i < cells; i++) {
            int diff = start - allElements[i];
            if (diff % x != 0) {
                return -1;
            }
            actions[i] = diff / x;
            sumOfActions += abs(actions[i]);
        }

        return sumOfActions;
    }

    // Uses average on number of actions, but it fails in some cases
    // int minOperations(vector<vector<int>> &grid, int x) {
    //     int height = grid.size();
    //     int width = grid[0].size();
    //     int start = grid[0][0];
    //     vector<vector<int>> actionGrid(height, vector<int>(width));
    //     int sumOfActions = 0;
    //     for (int row = 0; row < height; row++) {
    //         for (int col = 0; col < width; col++) {
    //             int diff = start - grid[row][col];
    //             if (diff % x != 0) {
    //                 return -1;
    //             }
    //             actionGrid[row][col] = diff / x;
    //             sumOfActions += actionGrid[row][col];
    //         }
    //     }
    //
    //     int A = sumOfActions / (height * width); // Amount of actions to "remove" on each cell
    //     sumOfActions = 0;
    //     for (int row = 0; row < height; row++) {
    //         for (int col = 0; col < width; col++) {
    //             actionGrid[row][col] -= A;
    //             sumOfActions += abs(actionGrid[row][col]);
    //         }
    //     }
    //
    //     return sumOfActions;
    // }
};

int main() {
    TestSuite<int, vector<vector<int>>, int> testSuite("Minimum operations", "grid", "x");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {{2, 4}, {6, 8}},
            2,
        },
        {
            5,
            {{1, 5}, {2, 3}},
            1,
        },
        {
            -1,
            {{1, 2}, {3, 4}},
            2,
        },
        // Submission test cases
        {
            25,
            {{529, 529, 989}, {989, 529, 345}, {989, 805, 69}},
            92,
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minOperations, testSuite);
}
