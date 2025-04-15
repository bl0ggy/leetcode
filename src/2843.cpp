#include "common.h"

class Solution {
  public:
    int countSymmetricIntegers(int low, int high) {
        int count = 0;
        for (int value = low; value <= high; value++) {
            string valueStr = to_string(value);
            if (valueStr.length() % 2 == 1) {
                continue;
            }
            int n = valueStr.length() / 2;
            int a = 0, b = 0;
            for (int i = 0; i < n; i++) {
                a += valueStr[i] - '0';
                b += valueStr[n + i] - '0';
            }
            if (a == b) {
                count++;
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
