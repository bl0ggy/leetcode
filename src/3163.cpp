#include "common.h"

class Solution {
  public:
    string compressedString(string word) {
        string answer(word.length() * 2, 0);
        size_t wordLength = word.length();
        int count = 1;
        size_t i, j;
        for (i = 1, j = 0; i < wordLength; i++) {
            if (word[i] != word[i - 1]) {
                answer[j++] = (char)(48 + count);
                answer[j++] = word[i - 1];
                count = 1;
            } else {
                if (count == 9) {
                    answer[j++] = (char)(48 + count);
                    answer[j++] = word[i - 1];
                    count = 1;
                } else {
                    count++;
                }
            }
        }
        answer[j++] = (char)(48 + count);
        answer[j++] = word[i - 1];
        answer.resize(j);

        return answer;
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
