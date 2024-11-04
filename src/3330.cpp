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
    const string nameInput = "word";
    const string nameOutput = "possible string count";
    vector<TestCase<string, int>> testCases{
        {
            {nameInput, "abbcccc"},
            {nameOutput, 5},
        },
        {
            {nameInput, "abcd"},
            {nameOutput, 1},
        },
        {
            {nameInput, "aaaa"},
            {nameOutput, 4},
        },
        {
            {nameInput, "aabbbccccdddddefghijj"},
            {nameOutput, 12},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<string, int> testCase) {
        Solution solution;
        return solution.possibleStringCount(testCase.input);
    });
}
