#include "common.h"

class Solution {
  public:
    vector<int> maximumBeauty(vector<vector<int>> &items, vector<int> &queries) {
        int queriesSize = queries.size();
        vector<int> answer(queriesSize, 0);
        map<int, vector<int>> queriesMap; // key: price, value: vec of indexes

        sort(items.begin(), items.end());
        for (int q = 0; q < queriesSize; q++) {
            queriesMap[queries[q]].push_back(q);
        }

        // Map is sorted by key
        auto mapIt = queriesMap.begin();
        auto itemIt = items.begin();
        int maxBeauty = 0;
        while (mapIt != queriesMap.end()) {
            while (itemIt != items.end() && (*itemIt)[0] <= mapIt->first) {
                maxBeauty = max(maxBeauty, (*itemIt)[1]);
                itemIt++;
            }
            for (auto it : mapIt->second) {
                answer[it] = maxBeauty;
            }
            mapIt++;
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
