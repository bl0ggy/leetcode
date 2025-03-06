#include "common.h"

class Solution {
  public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>> &grid) {
        int size = grid.size();
        int squareSize = size * size;
        int numbers[50 * 50 + 1];
        for (auto &n : numbers) {
            n = 0;
        }

        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                numbers[grid[y][x]]++;
            }
        }

        int a = 0, b = 0;
        for (int i = 1; i <= squareSize; i++) {
            if (numbers[i] == 0) {
                b = i;
            } else if (numbers[i] == 2) {
                a = i;
            }
        }

        return {a, b};
    }
};

int main() {
    TestSuite<vector<int>, vector<vector<int>>> testSuite("Missing and repeated values", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            {2, 4},
            {{1, 3}, {2, 2}},
        },
        {
            {9, 5},
            {{9, 1, 7}, {8, 9, 2}, {3, 4, 6}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::findMissingAndRepeatedValues, testSuite);
}
