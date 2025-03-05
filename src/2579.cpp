#include "common.h"

class Solution {
  public:
    long long coloredCells(int n) {
        n--;
        long long longN = n;
        long long sumN = longN * (longN + 1) / 2;
        return 1LL + 4LL * sumN;
    }
};

int main() {
    TestSuite<long long, int> testSuite("Colored cells", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            1,
            1,
        },
        {
            5,
            2,
        },
        // Submission test cases
        // My test cases
        {
            199980001,
            10000,
        },
        {
            19999800001,
            100000,
        },
        {
            1999998000001,
            1000000,
        },
        {
            199999980000001,
            10000000,
        },
    });

    Main main;
    main.runTests(&Solution::coloredCells, testSuite);
}
