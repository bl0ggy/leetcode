#include "common.h"

class Solution {
  public:
    long long minEnd(int n, int x) {
        long long minimumEnd = x;

        for (int i = 1; i < n; i++) {
            minimumEnd = (minimumEnd + 1) | x;
        }

        return minimumEnd;
    }
};

int main() {
    TestSuite<long long, int, int> testSuite("minimum end", "n", "x");
    testSuite.addTestCases({
        // Orignal test cases
        {
            // {4,5,6}
            // 4 : 0b00000100
            // 5 : 0b00000101
            // 6 : 0b00000110
            6, //  0b00000110
            3, //  0b00000011
            4, //  0b00000100
        },
        {
            // {7,15}
            // 7 : 0b00000111
            // 15: 0b00001111
            15, // 0b00001111
            2,  // 0b00000010
            7,  // 0b00000111
        },
        // Submit test cases
        {
            // {1,3,5}
            // 1: 0b00000001
            // 3: 0b00000011
            // 5: 0b00000101
            5, // 0b00000101
            3, // 0b00000011
            1, // 0B00000001
        },
    });

    Main main;
    return main.runTests(&Solution::minEnd, testSuite);
}
