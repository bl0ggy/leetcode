#include "common.h"

class Solution {
  public:
    int maximumCandies(vector<int> &candies, long long k) {
        int sizeCandies = candies.size();
        int maxCandies = *max_element(candies.begin(), candies.end());
        int left = 1, right = maxCandies, middle = (left + right) / 2;
        maxCandies = 0;
        while (left <= right) {
            long long tmpK = k;
            for (int i = 0; i < sizeCandies; i++) {
                int c = candies[i];
                tmpK -= c / middle;
            }
            // Enough candies
            if (tmpK <= 0) {
                maxCandies = max(maxCandies, middle);
                left = middle + 1;
                middle = (left + right) / 2;
            } else {
                right = middle - 1;
                middle = (left + right) / 2;
            }
        }

        return maxCandies;
    }
};

int main() {
    TestSuite<int, vector<int>, long long> testSuite("Maximum candies", "candies", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {5, 8, 6},
            3,
        },
        {
            0,
            {2, 5},
            11,
        },
        // Submission test cases
        {
            0,
            {10000000},
            1000000000000,
        },
        // My test cases
        {
            20,
            {1, 1000, 1000},
            100,
        },
        {
            1,
            {7, 5},
            11,
        },
        {
            306,
            {41, 24, 63, 2453, 64, 123, 522, 7},
            9,
        },
    });

    Main main;
    main.runTests(&Solution::maximumCandies, testSuite);
}
