#include "common.h"

class Solution {
  public:
    string compressedString(string &word) {
        size_t wordLength = word.length();
        size_t twoWordLength = wordLength * 2;
        // Max output size is twice the word: "abcde" -> "1a1b1c1d1e"
        // Will edit `word` directly, so we copy it to itself to make it twice as long
        word += word;
        char count = '1';
        size_t i, j;
        for (i = wordLength + 1, j = 0; i < twoWordLength; i++) {
            char c = word[i - 1];
            if (word[i] != c) {
                word[j++] = count;
                word[j++] = c;
                count = '1';
            } else {
                if (count == '9') {
                    word[j++] = count;
                    word[j++] = c;
                    count = '1';
                } else {
                    count++;
                }
            }
        }
        word[j++] = count;
        word[j++] = word[i - 1];
        word.resize(j);

        return word;
    }
};

int main() {
    const string nameInput = "word";
    const string nameOutput = "compressed word";
    vector<TestCase<string, string>> testCases{
        {
            {nameInput, "abcde"},
            {nameOutput, "1a1b1c1d1e"},
        },
        {
            {nameInput, "aaaaaaaaaaaaaabb"},
            {nameOutput, "9a5a2b"},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<string, string> &testCase) {
        Solution solution;
        return solution.compressedString(testCase.input);
    });
}
