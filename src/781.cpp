#include "common.h"
#include <numeric>

class Solution {
  public:
    int numRabbits(vector<int> &answers) {
        int numRabbits = 0;
        int size = answers.size();
        sort(answers.begin(), answers.end());
        vector<int> answersCount(1001, 0);
        for (int i = 0; i < size; i++) {
            answersCount[answers[i] + 1]++;
        }
        for (int i = 1; i < 1001; i++) {
            if (answersCount[i] > 0) {
                numRabbits += floor((double)answersCount[i] / i) * i;
                if ((answersCount[i] % i) > 0) {
                    numRabbits += i;
                }
            }
        }

        return numRabbits;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("781", "answers");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {1, 1, 2},
        },
        {
            11,
            {10, 10, 10},
        },
        // My test cases
        {
            1,
            {0},
        },
        {
            4,
            {1, 1, 1},
        },
        {
            6,
            {2, 2, 2, 2},
        },
        {
            6,
            {2, 2, 2, 2, 2},
        },
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::numRabbits, testSuite);
}
