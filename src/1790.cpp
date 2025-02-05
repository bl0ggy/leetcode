#include "common.h"

class Solution {
  public:
    bool areAlmostEqual(string s1, string s2) {
        int length = s1.length();
        int lastDiff = -1;
        int diffCount = 0;
        for (int i = 0; i < length; i++) {
            if (s1[i] != s2[i]) {
                diffCount++;
                if (diffCount > 2) {
                    return false;
                }
                if (lastDiff != -1) {
                    if (s1[lastDiff] != s2[i] || s1[i] != s2[lastDiff]) {
                        cout << "a" << endl;
                        return false;
                    }
                    lastDiff = -1;
                } else {
                    lastDiff = i;
                }
            }
        }

        return lastDiff == -1;
    }
};

int main() {
    TestSuite<bool, string, string> testSuite("Alsmot equal", "s1", "s2");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            "bank",
            "kanb",
        },
        {
            false,
            "attack",
            "defend",
        },
        {
            true,
            "kelb",
            "kelb",
        },
        {
            false,
            "qgqeg",
            "gqgeq",
        },
        // Submission test cases
        // My test cases
        {
            false,
            "abcde",
            "ebcad",
        },
    });

    Main main;
    main.runTests(&Solution::areAlmostEqual, testSuite);
}
