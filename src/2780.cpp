#include "common.h"

class Solution {
  public:
    int minimumIndex(vector<int> &nums) {
        unordered_map<int, int> dominants;
        for (auto &i : nums) {
            dominants[i]++;
        }
        auto it = dominants.begin();
        auto dominant = it;
        for (; it != dominants.end(); it++) {
            if (it->second > dominant->second) {
                dominant = it;
            }
        }

        int validIndex = -1, dominantCount = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == dominant->first) {
                dominantCount++;
                if (dominantCount * 2 > i + 1) {
                    validIndex = i;
                    break;
                }
            }
        }

        if (validIndex == -1) { // Impossible, it's guaranteed to have a dominant number
            return -1;
        }

        if (((dominant->second - dominantCount) * 2) <= (nums.size() - validIndex - 1)) {
            return -1;
        }

        return validIndex;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Minium index", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {1, 2, 2, 2},
        },
        {
            4,
            {2, 1, 3, 1, 1, 1, 7, 1, 2, 1},
        },
        {
            -1,
            {3, 3, 3, 3, 7, 2, 2},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minimumIndex, testSuite);
}
