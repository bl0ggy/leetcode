#include "common.h"

class Solution {
  public:
    int findMaxFish(vector<vector<int>> &grid) {
        int ans = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        vector<int> urdl = {-1, 0, 1, 0, -1};

        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                deque<pair<int, int>> queue;
                queue.push_back({row, col});
                int sum = 0;
                while (queue.size()) {
                    auto [crow, ccol] = queue.front();
                    queue.pop_front();
                    if (visited[crow][ccol]) {
                        continue;
                    }
                    visited[crow][ccol] = true;
                    if (grid[crow][ccol] == 0) {
                        continue;
                    }

                    sum += grid[crow][ccol];
                    for (int i = 0; i < 4; i++) {
                        int r = crow + urdl[i];
                        int c = ccol + urdl[i + 1];
                        if (r >= 0 && r < rows && c >= 0 && c < cols && !visited[r][c]) {
                            queue.push_back({r, c});
                        }
                    }
                }
                ans = max(ans, sum);
            }
        }

        return ans;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>> testSuite("Max fishes", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            7,
            {{0, 2, 1, 0}, {4, 0, 0, 3}, {1, 0, 0, 4}, {0, 3, 2, 0}},
        },
        {
            1,
            {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}},
        },
        // Submission test cases
        {
            22,
            {{8, 6}, {2, 6}},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::findMaxFish, testSuite);
}
