#include "common.h"

class Solution {
  public:
    int minOperations(vector<int> &nums, int k) {
        priority_queue<int, vector<int>, greater<int>> queue(nums.begin(), nums.end());
        int num1, num2;
        int i = 0;
        while (queue.top() < k && queue.size() >= 2) {
            num1 = queue.top();
            queue.pop();
            num2 = queue.top();
            queue.pop();
            long long newNum = (long long)num1 * 2 + num2;
            if (newNum < k) {
                queue.push((int)newNum);
            }
            i++;
        };
        if (queue.size() == 1 && queue.top() < k) {
            i++;
        }
        return i;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("Minimum operations", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {2, 11, 10, 1, 3},
            10,
        },
        {
            4,
            {1, 1, 2, 4, 9},
            20,
        },
        // Submission test cases
        {
            2,
            {999999999, 999999999, 999999999},
            1000000000,
        },
        {
            2,
            {9, 98, 52, 8},
            98,
        },
        {
            4,
            {62, 32, 62, 73, 58, 56, 68, 50},
            74,
        },
        {
            3,
            {97, 73, 5, 78},
            98,
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minOperations, testSuite);
}
