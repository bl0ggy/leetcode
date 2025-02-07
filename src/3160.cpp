#include "common.h"

class Solution {
  public:
    // Memory limit exceeded!
    vector<int> queryResults(int limit, vector<vector<int>> &queries) {
        int queriesSize = queries.size();
        int numberOfBalls = limit + 1;
        map<int, int> colorCount;
        vector<int> ballToColor(numberOfBalls, 0);
        vector<int> ans(queriesSize, 0);
        int currentDistinctColors = 0;
        for (int i = 0; i < queriesSize; i++) {
            int ball = queries[i][0];
            int color = queries[i][1];
            if (ballToColor[ball] == color) {
                ans[i] = currentDistinctColors;
                continue;
            }

            if (ballToColor[ball] > 0) {
                colorCount[ballToColor[ball]]--;
                if (colorCount[ballToColor[ball]] == 0) {
                    currentDistinctColors--;
                }
            }

            ballToColor[ball] = color;
            colorCount[color]++;
            if (colorCount[color] == 1) {
                currentDistinctColors++;
            }
            ans[i] = currentDistinctColors;
        }

        return ans;
    }
};

int main() {
    TestSuite<vector<int>, int, vector<vector<int>>> testSuite("Distinct colors", "limit", "queries");
    testSuite.addTestCases({
        // Original test cases
        {
            {1, 2, 2, 3},
            4,
            {{1, 4}, {2, 5}, {1, 3}, {3, 4}},
        },
        {
            {1, 2, 2, 3, 4},
            4,
            {{0, 1}, {1, 2}, {2, 2}, {3, 4}, {4, 5}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::queryResults, testSuite);
}
