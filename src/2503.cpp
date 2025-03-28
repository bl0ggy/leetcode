#include "common.h"

class Solution {
  public:
    vector<int> maxPoints(vector<vector<int>> &grid, vector<int> &queries) {
        int height = grid.size();
        int width = grid[0].size();
        unordered_map<int, int> queryToCount;
        vector<int> sortedQueries = queries;
        sort(sortedQueries.begin(), sortedQueries.end());

        const array<int, 5> urdl = {-1, 0, 1, 0, -1};

        int queryIndex = 0;
        vector<vector<bool>> visited(height, vector<bool>(width));
        deque<pair<int, int>> nextQueue, currentQueue;
        int points = 0;
        visited[0][0] = true;
        nextQueue.push_front({0, 0});
        while (queryIndex < queries.size()) {
            swap(nextQueue, currentQueue);
            while (!currentQueue.empty()) {
                auto [currentRow, currentColumn] = currentQueue.front();
                currentQueue.pop_front();

                if (grid[currentRow][currentColumn] >= sortedQueries[queryIndex]) {
                    nextQueue.push_back({currentRow, currentColumn});
                    continue;
                }

                points++;

                for (int i = 0; i < 4; i++) {
                    int nextRow = urdl[i] + currentRow, nextColumn = urdl[i + 1] + currentColumn;
                    if (nextRow >= 0 && nextColumn >= 0 && nextRow < height && nextColumn < width && !visited[nextRow][nextColumn]) {
                        visited[nextRow][nextColumn] = true;
                        currentQueue.push_back({nextRow, nextColumn});
                    }
                }
            }

            queryToCount[sortedQueries[queryIndex]] = points;
            queryIndex++;
        }

        for (int i = 0; i < queries.size(); i++) {
            queries[i] = queryToCount[queries[i]];
        }

        return queries;
    }
};

int main() {
    TestSuite<vector<int>, vector<vector<int>>, vector<int>> testSuite("Max points", "grid", "queries");
    testSuite.addTestCases({
        // Original test cases
        {
            {5, 8, 1},
            {{1, 2, 3}, {2, 5, 7}, {3, 5, 1}},
            {5, 6, 2},
        },
        {
            {0},
            {{5, 2, 1}, {1, 1, 2}},
            {3},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maxPoints, testSuite);
}
