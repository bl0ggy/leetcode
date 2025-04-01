#include "common.h"
#include <numeric>

class Solution {
  public:
    long long putMarbles(vector<int> &weights, int k) {
        int size = weights.size();
        vector<int> prefixSum(size - 1);
        for (int i = 0; i < size - 1; i++) {
            prefixSum[i] = weights[i] + weights[i + 1];
        }
        sort(prefixSum.begin(), prefixSum.end());

        long long ans = 0;
        for (int i = 0; i < k - 1; i++) {
            ans += prefixSum[size - i - 2] - prefixSum[i];
        }

        return ans;
    }
};

int main() {
    TestSuite<long long, vector<int>, int> testSuite("Diff marbles", "weights", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {1, 3, 5, 1},
            2,
        },
        {
            0,
            {1, 3},
            2,
        },
        // Submission test cases
        // My test cases
        {
            5,
            {2, 7, 3, 4, 3},
            3,
        },
        {
            3,
            {2, 7, 3, 4, 3},
            2,
        },
    });

    Main main;
    main.runTests(&Solution::putMarbles, testSuite);
}
