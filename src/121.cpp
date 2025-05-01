#include "common.h"

class Solution {
  public:
    int maxProfit(vector<int> &prices) {
        int size = prices.size();
        int minValue = INT_MAX, maxValue = 0;
        int ans = 0;

        for (int i = 0; i < size; i++) {
            if (prices[i] < minValue) {
                maxValue = prices[i];
                minValue = prices[i];
            }
            maxValue = max(maxValue, prices[i]);
            ans = max(ans, maxValue - minValue);
        }

        return ans;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("121", "prices");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {7, 1, 5, 3, 6, 4},
        },
        {
            0,
            {7, 6, 4, 3, 1},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maxProfit, testSuite);
}
