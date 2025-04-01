#include "common.h"

class Solution {
  public:
    long long mostPoints(vector<vector<int>> &questions) {
        int size = questions.size();
        vector<long long> maxPoints(size, 0);
        long long ans = 0;
        for (int i = size - 1; i >= 0; i--) {
            maxPoints[i] = recurse(i, 0, questions, maxPoints);
            ans = max(ans, maxPoints[i]);
        }

        return ans;
    }

    long long recurse(int index, const long long &value, const vector<vector<int>> &questions, vector<long long> &maxPoints) {
        if (index >= maxPoints.size()) {
            return value;
        }
        if (maxPoints[index]) {
            return value + maxPoints[index];
        }

        return max(recurse(index + questions[index][1] + 1, value + questions[index][0], questions, maxPoints), recurse(index + 1, value, questions, maxPoints));
    }
};

int main() {
    TestSuite<long long, vector<vector<int>>> testSuite("Max points", "questions");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {{3, 2}, {4, 3}, {4, 4}, {2, 5}},
        },
        {
            7,
            {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::mostPoints, testSuite);
}
