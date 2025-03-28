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
        using qType = pair<int, pair<int, int>>;
        priority_queue<qType, vector<qType>, greater<>> lesserQueue; // cellValue,(row,col))
        int points = 0;
        visited[0][0] = true;
        lesserQueue.push({grid[0][0], {0, 0}});
        while (queryIndex < queries.size()) {
            int queryValue = sortedQueries[queryIndex];
            while (!lesserQueue.empty() && queryValue > lesserQueue.top().first) {
                auto [queueValue, cellRef] = lesserQueue.top();
                auto [currentRow, currentColumn] = cellRef;
                lesserQueue.pop();

                points++;

                for (int i = 0; i < 4; i++) {
                    int nextRow = urdl[i] + currentRow, nextColumn = urdl[i + 1] + currentColumn;
                    if (nextRow >= 0 && nextColumn >= 0 && nextRow < height && nextColumn < width && !visited[nextRow][nextColumn]) {
                        visited[nextRow][nextColumn] = true;
                        lesserQueue.push({grid[nextRow][nextColumn], {nextRow, nextColumn}});
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
