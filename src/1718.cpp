#include "common.h"

class Solution {
  public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> ans(2 * n - 1, 0);
        vector<bool> usedNumbers(n + 1, false);
        next(0, n, ans, usedNumbers);
        return ans;
    }

    bool next(int currentIndex, int n, vector<int> &sequence, vector<bool> &usedNumbers) {
        if (currentIndex >= sequence.size()) {
            return true;
        }
        if (sequence[currentIndex] != 0) {
            return next(currentIndex + 1, n, sequence, usedNumbers);
        }

        for (int number = n; number > 0; number--) {
            if (usedNumbers[number]) {
                continue;
            }

            usedNumbers[number] = true;
            sequence[currentIndex] = number;

            if (number == 1) {
                if (next(currentIndex + 1, n, sequence, usedNumbers)) {
                    return true;
                }
            } else if (currentIndex + number < sequence.size() && sequence[currentIndex + number] == 0) {
                sequence[currentIndex + number] = number;
                if (next(currentIndex + 1, n, sequence, usedNumbers)) {
                    return true;
                }
                sequence[currentIndex + number] = 0;
            }

            sequence[currentIndex] = 0;
            usedNumbers[number] = false;
        }

        return false;
    }
};

int main() {
    TestSuite<vector<int>, int> testSuite("Distance sequence", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            {3, 1, 2, 3, 2},
            3,
        },
        //       _________
        // add 5 5____5___
        // mov 4 5_4__54__
        // add 3 53_4354__
        // add 2 impossible
        // mov 3 5_4_3543_
        // add 2 52423543_
        // add 1 524235431 works but not lexico highest
        // rem 2 (can't move it)
        // rem 3 (can't move it)
        // mov 4 5__4_5_4_
        // repeat...
        {
            {5, 3, 1, 4, 3, 5, 2, 4, 2},
            5,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::constructDistancedSequence, testSuite);
}
