#include "common.h"

class Solution {
  public:
    int numberOfSubstrings(string s) {
        int length = s.length();
        unordered_map<char, int> characters{{'a', 0}, {'b', 0}, {'c', 0}};
        int left = 0, right = 0;
        int substringsCount = 0;
        while (right <= length && left < length) {
            while (right < length && (characters['a'] == 0 || characters['b'] == 0 || characters['c'] == 0)) {
                characters[s[right]]++;
                right++;
            }

            if (characters['a'] > 0 && characters['b'] > 0 && characters['c'] > 0) {
                substringsCount += length - right + 1;
            }

            characters[s[left]]--;
            left++;
        }

        return substringsCount;
    }
};

int main() {
    TestSuite<int, string> testSuite("Number of substrings", "s");
    testSuite.addTestCases({
        // Original test cases
        {
            10,
            "abcabc",
        },
        {
            3,
            "aaacb",
        },
        {
            1,
            "abc",
        },
        // Submission test cases
        // My test cases
        {
            22,
            "abcaaacba",
        },
    });

    Main main;
    main.runTests(&Solution::numberOfSubstrings, testSuite);
}
