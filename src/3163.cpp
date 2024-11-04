#include "common.h"

class Solution {
  public:
    string compressedString(string word) {
        stringstream answer;
        size_t wordLength = word.length();
        int count = 1;
        size_t i;
        for (i = 1; i < wordLength; i++) {
            if (word[i] != word[i - 1]) {
                answer << count << word[i - 1];
                count = 1;
            } else {
                if (count == 9) {
                    answer << count << word[i - 1];
                    count = 1;
                } else {
                    count++;
                }
            }
        }
        answer << count << word[i - 1];
        return answer.str();
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
