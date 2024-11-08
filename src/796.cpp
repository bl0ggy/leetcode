#include "common.h"

class Solution {
  public:
    bool rotateString(string s, string goal) {
        int sLength = s.length();
        int goalLength = goal.length();
        if (sLength != goalLength) {
            return false;
        }
        bool found = false;
        for (int i = 0; i < sLength; i++) {
            found = true;
            for (int j = 0; j < sLength; j++) {
                if (s[(i + j) % sLength] != goal[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        return found;
    }
};

int main() {
    TestSuite<bool, string, string> testSuite("rotatable string", "s", "goal");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            "abcde",
            "cdeab",
        },
        {
            false,
            "abcde",
            "abced",
        },
    });

    Main main;
    return main.runTests(&Solution::rotateString, testSuite);
}
