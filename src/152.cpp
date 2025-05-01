#include "common.h"

class Solution {
  public:
    int maxProduct(vector<int> &nums) {
        int size = nums.size();
        int answer = nums[0];
        int left = 1, right = 1;

        for (int i = 0; i < size; i++) {
            left *= nums[i];
            right *= nums[size - i - 1];
            answer = max(answer, max(left, right));
            if (nums[i] == 0) {
                left = 1;
            }
            if (nums[size - i - 1] == 0) {
                right = 1;
            }
        }

        return answer;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("152", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            6,
            {2, 3, -2, 4},
        },
        {
            0,
            {-2, 0, -1},
        },
        // My test cases
        {
            12,
            {2, 2, 0, 3, 4},
        },
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::maxProduct, testSuite);
}
