#include "common.h"

class Solution {
  public:
    void gray(vector<int> &input, int level) {
        if (level <= 0) {
            return;
        }
        gray(input, level - 1);
        input.push_back(input.back() ^ (1 << (level - 1)));
        gray(input, level - 1);
    }

    vector<int> grayCode(int n) {
        vector<int> answer;
        answer.reserve(n);
        answer.push_back(0);
        gray(answer, n);

        return answer;
    }
};

int main() {
    const string nameInput = "n";
    const string nameOutput = "gray code";
    vector<TestCase<int, vector<int>>> testCases{
        {
            {nameInput, 1},
            {nameOutput, {0, 1}},
        },
        {
            {nameInput, 2},
            {nameOutput, {0, 1, 3, 2}},
        },
        {
            {nameInput, 3},
            {nameOutput, {0, 1, 3, 2, 6, 7, 5, 4}},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<int, vector<int>> testCase) {
        Solution solution;
        return solution.grayCode(testCase.input);
    });
}
