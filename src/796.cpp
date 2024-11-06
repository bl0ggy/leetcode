#include "common.h"

class Solution {
  public:
    bool rotateString(string s, string goal) {
        int sLength = s.length();
        int goalLength = goal.length();
        if (sLength != goalLength) {
            return false;
        }
        bool found = false;
        for (int i = 0; i < sLength; i++) {
            found = true;
            for (int j = 0; j < sLength; j++) {
                if (s[(i + j) % sLength] != goal[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        return found;
    }
};

int main() {
    const string nameInput1 = "s";
    const string nameInput2 = "goal";
    const string nameOutput = "rotatable string";
    vector<TestCase<string, string, bool>> testCases{
        // Original test cases
        {
            {nameInput1, "abcde"},
            {nameInput2, "cdeab"},
            {nameOutput, true},
        },
        {
            {nameInput1, "abcde"},
            {nameInput2, "abced"},
            {nameOutput, false},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<string, string, bool> testCase) {
        Solution solution;
        return solution.rotateString(testCase.input1, testCase.input2);
    });
}
