#include "common.h"
#include <numeric>

class Solution {
  public:
    // Nothing fancy, we need to iterate over all member, O(n)
    int calPoints(vector<string> &operations) {
        int size = operations.size();
        vector<int> result = vector<int>(size, 0);
        int j = 0;
        for (int i = 0; i < size; i++) {
            if (operations[i] == "+") {
                result[j] = result[j - 2] + result[j - 1];
                j++;
            } else if (operations[i] == "C") {
                j--;
            } else if (operations[i] == "D") {
                result[j] = 2 * result[j - 1];
                j++;
            } else {
                result[j] = atoi(operations[i].c_str());
                j++;
            }
        }

        return reduce(result.begin(), result.begin() + j);
    }
};

int main() {
    TestSuite<int, vector<string>> testSuite("sum", "operations");
    testSuite.addTestCases({
        // Original test cases
        {
            30,
            {"5", "2", "C", "D", "+"},
        },
        {
            27,
            {"5", "-2", "4", "C", "D", "9", "+", "+"},
        },
        {
            0,
            {"1", "C"},
        },
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::calPoints, testSuite);
}
