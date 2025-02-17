#include "common.h"

class Solution {
  public:
    int numTilePossibilities(string tiles) {
        array<int, 26> chars;
        for (auto &c : chars) {
            c = 0;
        }
        for (char c : tiles) {
            chars[c - 'A']++;
        }
        return findPossibilities(chars);
    }
    int findPossibilities(array<int, 26> &chars) {
        int count = 0;
        for (int i = 0; i < 26; i++) {
            if (chars[i] <= 0) {
                continue;
            }
            chars[i]--;
            count++;
            count += findPossibilities(chars);
            chars[i]++;
        }
        return count;
    }
};

int main() {
    TestSuite<int, string> testSuite("Possibilities", "tiles");
    testSuite.addTestCases({
        // Original test cases
        {
            8,
            "AAB",
        },
        {
            188,
            "AAABBC",
        },
        {
            1,
            "V",
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::numTilePossibilities, testSuite);
}
