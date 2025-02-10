#include "common.h"

class Solution {
  public:
    string clearDigits(string s) {
        int length = s.length();
        int lettersToRemove = 0;
        for (int i = length - 1; i >= 0; i--) {
            if (s[i] >= '0' && s[i] <= '9') {
                s.erase(i, 1);
                lettersToRemove++;
            } else if (lettersToRemove && s[i] >= 'a' && s[i] <= 'z') {
                s.erase(i, 1);
                lettersToRemove--;
            }
        }
        return s;
    }
};

int main() {
    TestSuite<string, string> testSuite("String without digits", "s");
    testSuite.addTestCases({
        // Original test cases
        {
            "abc",
            "abc",
        },
        {
            "",
            "cb34",
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::clearDigits, testSuite);
}
