#include "common.h"

class Solution {
  public:
    bool checkValidCuts(int n, vector<vector<int>> &rectangles) {
        sort(rectangles.begin(), rectangles.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0] || (a[0] == b[0] && a[2] < b[2]); });
        int x = rectangles[0][2], indexX = 1;
        int countSplitX = 0;
        while (indexX < rectangles.size() && (countSplitX < 2 || x < n)) {
            if (x <= rectangles[indexX][0]) {
                countSplitX++;
            }
            x = max(x, rectangles[indexX][2]);
            indexX++;
        }

        if (countSplitX >= 2) {
            return true;
        }

        sort(rectangles.begin(), rectangles.end(), [](vector<int> &a, vector<int> &b) { return a[1] < b[1] || (a[1] == b[1] && a[3] < b[3]); });
        int y = rectangles[0][3], indexY = 1;
        int countSplitY = 0;
        while (indexY < rectangles.size() && (countSplitY < 2 || y < n)) {
            if (y <= rectangles[indexY][1]) {
                countSplitY++;
            }
            y = max(y, rectangles[indexY][3]);
            indexY++;
        }

        return countSplitY >= 2;
    }
};

int main() {
    TestSuite<bool, int, vector<vector<int>>> testSuite("Valid cuts", "n", "rectangles");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            5,
            {{1, 0, 5, 2}, {0, 2, 2, 4}, {3, 2, 5, 3}, {0, 4, 4, 5}},
        },
        {
            true,
            4,
            {{0, 0, 1, 1}, {2, 0, 3, 4}, {0, 2, 2, 3}, {3, 0, 4, 3}},
        },
        {
            false,
            4,
            {{0, 2, 2, 4}, {1, 0, 3, 2}, {2, 2, 3, 4}, {3, 0, 4, 2}, {3, 2, 4, 4}},
        },
        // Submission test cases
        {
            false,
            4,
            {{0, 0, 1, 4}, {1, 0, 2, 3}, {2, 0, 3, 3}, {3, 0, 4, 3}, {1, 3, 4, 4}},
        },
        // My test cases
        {
            // Not enough squares on x and y, 1 split on x, no split on y
            false,
            2,
            {{0, 0, 1, 1}, {1, 0, 2, 1}},
        },
        {
            // Enough squares on x and y, but only 1 split possible on both axes
            false,
            2,
            {{0, 0, 1, 1}, {1, 0, 2, 1}, {1, 1, 2, 2}},
        },
        {
            // With gaps on x
            true,
            7,
            {{1, 0, 2, 0}, {3, 0, 4, 0}, {5, 0, 6, 0}},
        },
        {
            // With gaps on y
            true,
            7,
            {{0, 1, 0, 2}, {0, 3, 0, 4}, {0, 5, 0, 6}},
        },
    });

    Main main;
    main.runTests(&Solution::checkValidCuts, testSuite);
}
