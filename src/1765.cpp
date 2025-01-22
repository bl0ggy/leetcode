
#include "common.h"

class Solution {
    using T = tuple<int, int>;
    vector<int> urdl = {-1, 0, 1, 0, -1};

  public:
    vector<vector<int>> highestPeak(vector<vector<int>> &isWater) {
        int rows = isWater.size();
        int cols = isWater[0].size();
        deque<T> queue;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (isWater[row][col] == 1) { // Water
                    queue.push_front({row, col});
                    isWater[row][col] = 0;
                } else {
                    isWater[row][col] = -1;
                }
            }
        }

        while (queue.size()) {
            auto [row, col] = queue.front();
            queue.pop_front();

            for (int i = 0; i < 4; i++) {
                int y = row + urdl[i];
                int x = col + urdl[i + 1];
                if (y >= 0 && y < rows && x >= 0 && x < cols && isWater[y][x] == -1) {
                    queue.push_back({y, x});
                    isWater[y][x] = isWater[row][col] + 1;
                }
            }
        }
        return isWater;
    }
};

int main() {
    TestSuite<vector<vector<int>>, vector<vector<int>>> testSuite("Height map", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            {
                {1, 0},
                {2, 1},
            },
            {
                {0, 1},
                {0, 0},
            },
        },
        {
            {
                {1, 1, 0},
                {0, 1, 1},
                {1, 2, 2},
            },
            {
                {0, 0, 1},
                {1, 0, 0},
                {0, 0, 0},
            },
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::highestPeak, testSuite);
}
