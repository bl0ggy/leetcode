#include "common.h"

class Solution {
  public:
    int minimumRecolors(string blocks, int k) {
        int length = blocks.length();
        int minRecolors = INT_MAX;
        int left = 0, right = 0;
        int sumWhite = 0;
        for (int i = 0; i < k; i++) {
            if (blocks[i] == 'W') {
                sumWhite++;
            }
        }
        right = k;
        while (right <= length) {
            minRecolors = min(minRecolors, sumWhite);
            if (blocks[left] == 'W') {
                sumWhite--;
            }
            if (blocks[right] == 'W') {
                sumWhite++;
            }
            right++;
            left++;
        }

        return minRecolors;
    }
};

int main() {
    TestSuite<int, string, int> testSuite("Minimum recolors", "blocks", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            "WBBWWBBWBW",
            7,
        },
        {
            0,
            "WBWBBBW",
            2,
        },
        // Submission test cases
        {
            4,
            "BWBBWWBBBWBWWWBWWBBWBWBBWBB",
            11,
        },
        {
            3,
            "BWWWBB",
            6,
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minimumRecolors, testSuite);
}
