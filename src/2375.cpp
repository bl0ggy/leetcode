#include "common.h"

class Solution {
  public:
    string smallestNumber(string pattern) {
        int queue[10]{'1'}, queueIndex = 0, patternIndex = 0;
        int patternLength = pattern.length();
        for (int i = 0; i < patternLength; i++) {
            if (pattern[i] == 'I') {
                while (queueIndex >= 0) {
                    pattern[patternIndex] = queue[queueIndex];
                    patternIndex++;
                    queueIndex--;
                }
            }
            queueIndex++;
            queue[queueIndex] = i + 1 + '1';
        }
        while (queueIndex > 0) {
            pattern[patternIndex] = queue[queueIndex];
            patternIndex++;
            queueIndex--;
        }
        if (queueIndex == 0) {
            pattern.push_back(queue[queueIndex]);
        }
        return pattern;
    }
};

int main() {
    TestSuite<string, string> testSuite("Smallest number", "pattern");
    testSuite.addTestCases({
        // Original test cases
        {
            "123549876",
            "IIIDIDDD",
        },
        {
            "4321",
            "DDD",
        },
        // Submission test cases
        {
            "4321567",
            "DDDIII",
        },
        // My test cases
        {
            "213465879",
            "DIIIDIDI",
        },
        {
            "1234",
            "III",
        },
        {
            "21",
            "D",
        },
        {
            "12",
            "I",
        },
    });

    Main main;
    main.runTests(&Solution::smallestNumber, testSuite);
}
