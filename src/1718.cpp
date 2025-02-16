#include "common.h"

class Solution {
    vector<int> ans;

  public:
    // Time limit exceeded
    vector<int> constructDistancedSequence(int n) {
        int size = 2 * n - 1;
        ans = vector<int>(size, 0);
        vector<int> current(size, 0);
        next(current, size, n);
        auto it = find(ans.begin(), ans.end(), 0);
        *it = 1;
        return ans;
    }

    void next(vector<int> &sequence, int size, int nextNumber) {
        if (nextNumber == 1) {
            for (int i = 0; i < size; i++) {
                if (ans[i] < sequence[i]) {
                    ans = sequence;
                    return;
                } else if (ans[i] > sequence[i]) {
                    return;
                }
            }
        }

        for (int i = 0; i < size - nextNumber; i++) {
            int nextI = i + nextNumber;
            if (sequence[i] == 0 && nextI < size && sequence[nextI] == 0) {
                sequence[i] = nextNumber;
                sequence[nextI] = nextNumber;
                next(sequence, size, nextNumber - 1);
                sequence[i] = 0;
                sequence[nextI] = 0;
            }
        }
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
