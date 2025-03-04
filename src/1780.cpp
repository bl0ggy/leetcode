#include "common.h"

class Solution {
  public:
    const vector<int> powersOfThree = {
        1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721,
    };
    int powersOfThreeSize = powersOfThree.size();
    bool checkPowersOfThree(int n) {
        for (int i = 0; i < powersOfThreeSize; i++) {
            if (dfs(n, i)) {
                return true;
            }
        }
        return false;
    }

    bool dfs(int n, int i) {
        if (n == 0) {
            return true;
        }
        if (i >= powersOfThreeSize | n < 0) {
            return false;
        }

        return dfs(n - powersOfThree[i], i + 1) || dfs(n, i + 1);
    }
};

int main() {
    TestSuite<bool, int> testSuite("Power of three", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            12,
        },
        {
            true,
            91,
        },
        {
            false,
            21,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::checkPowersOfThree, testSuite);
}
