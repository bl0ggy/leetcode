#include "common.h"

class Solution {
    using T = tuple<int, int, int>;

  public:
    int trapRainWater(vector<vector<int>> &heightMap) {
        int n = heightMap.size();
        int m = heightMap[0].size();
        priority_queue<T, vector<T>, std::greater<T>> heap;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    heap.push({heightMap[i][j], i, j});
                    visited[i][j] = true;
                }
            }
        }

        int sum = 0;
        int level = -1;
        vector<int> dir = {-1, 0, 1, 0, -1};
        while (heap.size()) {
            auto cell = heap.top();
            heap.pop();
            level = max(level, get<0>(cell));

            for (int d = 0; d < 4; d++) {
                int i = get<1>(cell) + dir[d];
                int j = get<2>(cell) + dir[d + 1];
                if (i < 0 || i >= n || j < 0 || j >= m || visited[i][j]) {
                    continue;
                }
                visited[i][j] = true;
                heap.push({heightMap[i][j], i, j});
                if (heightMap[i][j] < level) {
                    sum += level - heightMap[i][j];
                }
            }
        }

        return sum;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>> testSuite("Trapped water sum", "Height map");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {{1, 4, 3, 1, 3, 2}, //
             {3, 2, 1, 3, 2, 4}, //
             {2, 3, 3, 2, 3, 1}},
        },
        {
            10,
            {{3, 3, 3, 3, 3}, //
             {3, 2, 2, 2, 3}, //
             {3, 2, 1, 2, 3}, //
             {3, 2, 2, 2, 3}, //
             {3, 3, 3, 3, 3}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::trapRainWater, testSuite);
}
