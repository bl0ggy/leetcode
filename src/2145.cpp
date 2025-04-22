#include "common.h"

class Solution {
  public:
    int numberOfArrays(vector<int> &differences, int lower, int upper) {
        int size = differences.size();
        int x = 0, y = 0, sum = 0;

        for (int i = 0; i < size; i++) {
            sum += differences[i];
            x = min(x, sum);
            y = max(y, sum);
            if ((y - x) > (upper - lower)) {
                return 0;
            }
        }

        return (upper - lower) - (y - x) + 1;
    }
};

int main() {
    TestSuite<int, vector<int>, int, int> testSuite("2145", "differences", "lower", "upper");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {1, -3, 4},
            1,
            6,
        },
        {
            4,
            {3, -4, 5, 1, -2},
            -4,
            5,
        },
        {
            0,
            {4, -7, 2},
            3,
            6,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::numberOfArrays, testSuite);
}
