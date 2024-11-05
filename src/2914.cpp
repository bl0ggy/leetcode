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
    const string nameInput = "s";
    const string nameOutput = "minimum changes";
    vector<TestCase<string, int>> testCases{
        // Original tests cases
        {
            {nameInput, "1001"}, // -> "0011" or "1100"
            {nameOutput, 2},
        },
        {
            {nameInput, "10"}, // -> "00" or "11"
            {nameOutput, 1},
        },
        {
            {nameInput, "0000"}, // -> "0000"
            {nameOutput, 0},
        },
        // My tests cases
        {
            {nameInput, "1000"}, // More 0s -> "0000" or "1100"
            {nameOutput, 1},
        },
        {
            {nameInput, "0111"}, // More 1s -> "0011" or "1111"
            {nameOutput, 1},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<string, int> testCase) {
        Solution solution;
        return solution.minChanges(testCase.input);
    });
}
