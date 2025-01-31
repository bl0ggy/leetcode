#include "common.h"

class Solution {
    using Cell = pair<int, int>;

  public:
    int largestIsland(vector<vector<int>> &grid) {
        constexpr array<int, 5> urdl{-1, 0, 1, 0, -1};
        int gridSize = grid.size();
        constexpr int maxGridSize = 500;
        array<int, maxGridSize> v;
        v.fill(0);
        array<array<int, maxGridSize>, maxGridSize> visited;
        visited.fill(v);
        unordered_map<int, int> groupSize;
        unordered_map<int, unordered_set<int>> zerosTouchingLand; // zero-cell -touches> group
        int currentGroup = 0;
        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                if (visited[row][col]) {
                    continue;
                }
                if (grid[row][col] == 0) {
                    continue;
                }

                currentGroup++;
                deque<Cell> queue;
                queue.push_back({row, col});
                int landSize = 0;
                while (queue.size()) {
                    auto [r, c] = queue.front();
                    queue.pop_front();
                    if (visited[r][c]) {
                        continue;
                    }
                    visited[r][c] = currentGroup;
                    for (int i = 0; i < 4; i++) {
                        int nextRow = r + urdl[i];
                        int nextCol = c + urdl[i + 1];
                        if (0 <= nextRow && nextRow < gridSize && 0 <= nextCol && nextCol < gridSize && visited[nextRow][nextCol] == 0) {
                            if (grid[nextRow][nextCol] == 1) {
                                queue.push_back({nextRow, nextCol});
                            } else {
                                zerosTouchingLand[nextRow * gridSize + nextCol].insert(currentGroup);
                            }
                        }
                    }

                    landSize++;
                }
                groupSize[currentGroup] = landSize;
            }
        }

        stringstream ss;
        for (int r = 0; r < gridSize; r++) {
            for (int c = 0; c < gridSize; c++) {
                ss << visited[r][c] << " ";
            }
            ss << "\n";
        }

        if (zerosTouchingLand.size() < 2) {
            if (currentGroup == 0) {
                return 1;
            }
            return gridSize * gridSize;
        }

        int maxLandSize = 0;
        for (auto [cell, groups] : zerosTouchingLand) {
            int sum = 1;
            for (auto group : groups) {
                sum += groupSize[group];
            }
            maxLandSize = max(maxLandSize, sum);
        }

        return maxLandSize;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>> testSuite("Biggest island", "grid");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {
                {1, 0},
                {0, 1},
            },
        },
        {
            4,
            {
                {1, 1},
                {1, 0},
            },
        },
        {
            4,
            {
                {1, 1},
                {1, 1},
            },
        },
        // Submission test cases
        // My test cases
        {
            9,
            {
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
                {1, 1, 0, 1, 1},
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 0},
            },
        },
        {
            8,
            {
                {0, 0, 1, 0, 0},
                {0, 0, 1, 0, 1},
                {1, 1, 0, 0, 1},
                {0, 0, 0, 0, 1},
                {1, 1, 1, 1, 0},
            },
        },
    });

    Main main;
    main.runTests(&Solution::largestIsland, testSuite);
}
