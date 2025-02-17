#include "common.h"

class Solution {
    unordered_set<string> existingPossibilities;

  public:
    // Slow
    int numTilePossibilities(string tiles) {
        findPossibilities("", tiles);
        return existingPossibilities.size() - 1; // Remove empty string
    }
    void findPossibilities(string currentChars, string remainingChars) {
        int length = remainingChars.length();
        if (length == 0) {
            existingPossibilities.insert(currentChars);
            return;
        }
        for (int i = 0; i < remainingChars.length(); i++) {
            findPossibilities(currentChars + remainingChars[i], remainingChars.substr(0, i) + remainingChars.substr(i + 1));
            findPossibilities(currentChars, remainingChars.substr(0, i) + remainingChars.substr(i + 1));
        }
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
