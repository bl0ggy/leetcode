#include "common.h"

class Solution {
  public:
    int minChanges(string s) {
        // Even length is an invalid test, so no need to early return
        int count = 0;
        // Since the substrings must be even, we only need to traverse every 2 characters and test by pair
        for (size_t i = 0; i < s.length(); i += 2) {
            if (s[i] != s[i + 1]) {
                count++;
            }
        }

        return count;
    }
};

int main() {
    TestSuite<int, string> testSuite("mnimum changes", "string");
    testSuite.addTestCases({
        // Original tests cases
        {
            2,
            "1001", // -> "0011" or "1100"
        },
        {
            1,
            "10", // -> "00" or "11"
        },
        {
            0,
            "0000", // -> "0000"
        },
        // My tests cases
        {
            0,
            "000011", // -> "000011"
        },
        {
            1,
            "1000", // More 0s -> "0000" or "1100"
        },
        {
            1,
            "0111", // More 1s -> "0011" or "1111"
        },
    });

    Main main;
    return main.runTests(&Solution::minChanges, testSuite);
}
