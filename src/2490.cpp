#include "common.h"

class Solution {
  public:
    bool isCircularSentence(string sentence) {
        if (sentence.front() == ' ' || sentence.back() == ' ') {
            return false;
        }

        int sentenceLength = sentence.length();
        for (int i = 1; i < sentenceLength - 1; i++) {
            auto pos = sentence.find(' ', i);
            if (pos == string::npos) {
                break;
            }
            if (sentence[pos - 1] != sentence[pos + 1]) {
                return false;
            }
            i = pos;
        }
        return sentence.front() == sentence.back();
    }
};

int main() {
    const string nameInput = "sentence";
    const string nameOutput = "is circular";
    vector<TestCase<string, bool>> testCases{
        // Original test cases
        {
            {nameInput, "leetcode exercises sound delightful"},
            {nameOutput, true},
        },
        {
            {nameInput, "eetcode"},
            {nameOutput, true},
        },
        {
            {nameInput, "Leetcode is cool"},
            {nameOutput, false},
        },
        // Submit test cases
        {
            {nameInput, "MuFoevIXCZzrpXeRmTssj lYSW U jM"},
            {nameOutput, false},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<string, bool> testCase) {
        Solution solution;
        return solution.isCircularSentence(testCase.input);
    });
}
