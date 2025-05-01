#include "common.h"

class Solution {
  public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int size = nums.size();
        vector<int> answer(size, 1);
        int current = 1;

        for (int i = 0; i < size; i++) {
            answer[i] *= current;
            current *= nums[i];
        }
        current = 1;
        for (int i = size - 1; i >= 0; i--) {
            answer[i] *= current;
            current *= nums[i];
        }

        return answer;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>> testSuite("238", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            {24, 12, 8, 6},
            {1, 2, 3, 4},
        },
        {
            {0, 0, 9, 0, 0},
            {-1, 1, 0, -3, 3},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::productExceptSelf, testSuite);
}
