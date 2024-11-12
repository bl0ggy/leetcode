#include "common.h"

class Solution {
  public:
    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries) {
        int itemsSize = items.size();
        int queriesSize = queries.size();
        vector<int> answer(queriesSize);

        for (int i = 0; i < itemsSize; i++) {
            for (int j = 0; j < queriesSize; j++) {
                if (items[i][0] <= queries[j]) {
                    answer[j] = max(answer[j], items[i][1]);
                }
            }
        }

        return answer;
    }
};

int main() {
    TestSuite<vector<int>, vector<vector<int>>, vector<int>> testSuite("", "", "");
    testSuite.addTestCases({
        // Original test cases
        {
            {2, 4, 5, 5, 6, 6},
            {{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}},
            {1, 2, 3, 4, 5, 6},
        },
        {
            {4},
            {{1, 2}, {1, 2}, {1, 3}, {1, 4}},
            {1},
        },
        {
            {0},
            {{10, 1000}},
            {5},
        },
    });

    Main main;
    main.runTests(&Solution::maximumBeauty, testSuite);
}
