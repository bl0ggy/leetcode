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
    TestSuite<bool, string> testSuite("is circular", "sentence");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            "leetcode exercises sound delightful",
        },
        {
            true,
            "eetcode",
        },
        {
            false,
            "Leetcode is cool",
        },
        // Submit test cases
        {
            false,
            "MuFoevIXCZzrpXeRmTssj lYSW U jM",
        },
    });

    Main main;
    return main.runTests(&Solution::isCircularSentence, testSuite);
}
