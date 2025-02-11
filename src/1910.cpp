#include "common.h"

class Solution {
  public:
    string removeOccurrences(string s, string part) {
        size_t i = 0;
        size_t partLength = part.length();
        while ((i = s.find(part, i >= partLength ? i - partLength : 0)) != string::npos) {
            s.erase(i, partLength);
        }
        return s;
    }
};

int main() {
    TestSuite<string, string, string> testSuite("Removed occurences", "s", "part");
    testSuite.addTestCases({
        // Original test cases
        {
            "dab",
            "daabcbaabcbc",
            "abc",
        },
        {
            "ab",
            "axxxxyyyyb",
            "xy",
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::removeOccurrences, testSuite);
}
