#include "common.h"

class Solution {
  public:
    int countSymmetricIntegers(int low, int high) {
        int count = 0;
        for (int value = low; value <= high; value++) {
            if (value < 10) {
                continue;
            } else if (value < 100) {
                int mod = value % 10;
                if (mod == (value / 10)) {
                    count++;
                }
            } else if (value < 1000) {
                continue;
            } else if (value < 10000) {
                int vLow = value % 100;
                int vHigh = value / 100;
                int modLow = vLow % 10;
                int modHigh = vHigh % 10;
                if ((modLow + vLow / 10) == (modHigh + vHigh / 10)) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    TestSuite<int, int, int> testSuite("2843", "low", "high");
    testSuite.addTestCases({
        // Original test cases
        {
            9,
            1,
            100,
        },
        {
            4,
            1200,
            1230,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countSymmetricIntegers, testSuite);
}
