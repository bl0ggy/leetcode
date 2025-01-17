#include "common.h"

class Solution {
  public:
    bool doesValidArrayExist(vector<int> &derived) {
        int size = derived.size();
        const vector<int> d(derived.begin(), derived.end());
        int original = 0; // Start with o[0] = 0. o[0] = 1 would work too
        for (int i = 1; i < size; i++) {
            original = d[i] ^ original;
        }
        return 0 == (d[0] ^ original);
    }
};

int main() {
    TestSuite<bool, vector<int>> testSuite("Original exists", "derived");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            {1, 1, 0},
        },
        {
            true,
            {1, 1},
        },
        {
            false,
            {1, 0},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::doesValidArrayExist, testSuite);
}
