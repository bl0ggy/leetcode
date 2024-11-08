#include "common.h"

class Solution {
  public:
    int possibleStringCount(string word) {
        int wordCount = 0;
        for (int i = 1; i < word.length(); i++) {
            if (word[i - 1] == word[i]) {
                wordCount++;
            }
        }

        return wordCount + 1;
    }
};

int main() {
    TestSuite<int, string> testSuite{"possible string count", "word"};
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            "abbcccc",
        },
        {
            1,
            "abcd",
        },
        {
            4,
            "aaaa",
        },
        // My test cases
        {
            12,
            "aabbbccccdddddefghijj",
        },
    });

    Main main;
    return main.runTests(&Solution::possibleStringCount, testSuite);
}
