#include "common.h"

class Solution {
  public:
    int numberOfAlternatingGroups(vector<int> &colors, int k) {
        int size = colors.size();
        int firstSameColor = -1;
        if (colors.front() == colors.back()) {
            firstSameColor = 0;
        } else {
            for (int i = 1; i < size; i++) {
                if (colors[i] == colors[i - 1]) {
                    firstSameColor = i;
                    break;
                }
            }
        }

        if (firstSameColor == -1) {
            return size;
        }

        int groups = 0;
        int currentCount = 1;
        for (int i = firstSameColor + 1; i < size; i++) {
            if (colors[i] == colors[i - 1]) {
                currentCount = 1;
            } else {
                currentCount++;
                if (currentCount >= k) {
                    groups++;
                }
            }
        }

        if (colors.front() != colors.back()) {
            currentCount++;
            if (currentCount >= k) {
                groups++;
            }
        }
        for (int i = 1; i < firstSameColor; i++) {
            if (colors[i] == colors[i - 1]) {
                currentCount = 1;
            } else {
                currentCount++;
                if (currentCount >= k) {
                    groups++;
                }
            }
        }

        return groups;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("two sum", "values", "target");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {0, 1, 0, 1, 0},
            3,
        },
        {
            2,
            {0, 1, 0, 0, 1, 0, 1},
            6,
        },
        {
            0,
            {1, 1, 0, 1},
            4,
        },
        // Submission test cases
        {
            4,
            {0, 1, 0, 1},
            3,
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::numberOfAlternatingGroups, testSuite);
}
