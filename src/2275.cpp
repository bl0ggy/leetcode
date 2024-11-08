#include "common.h"

class Solution {
  public:
    int largestCombination(vector<int> &candidates) {
        map<uint, int> mapOfCandidates;
        int maxCandidates = 0;
        for (uint i = 0; i < 32; i++) {
            mapOfCandidates[1 << i] = 0;
        }
        for (auto &p : mapOfCandidates) {
            for (int i = 0; i < candidates.size(); i++) {
                if (p.first & candidates[i]) {
                    p.second++;
                }
            }
        }
        for (auto &p : mapOfCandidates) {
            maxCandidates = max(maxCandidates, p.second);
        }

        return maxCandidates;
    }
};

int main() {
    const string nameInput = "candidates";
    const string nameOutput = "largest combination";
    TestSuite<int, vector<int>> testSuite("largest combination", "candidates");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {16, 17, 71, 62, 12, 24, 14},
        },
        {
            2,
            {8, 8},
        },
        // Submit test cases
        {
            28,
            {84, 40, 66, 44, 91, 90, 1, 14, 73, 51, 47, 35, 18, 46, 18, 65, 55, 18, 16, 45, 43, 58, 90, 92, 91, 43, 44, 76, 85, 72, 24, 89, 60, 94, 81, 90, 86, 79, 84, 41, 41, 28, 44},
        },
        // My tests
        {
            8,
            {1, 1, 1, 1, 1, 1, 1, 1},
        },
        {
            1,
            {1, 2, 4, 8, 16, 32, 64},
        },
    });

    Main main;
    return main.runTests(&Solution::largestCombination, testSuite);
}
