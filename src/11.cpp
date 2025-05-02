#include "common.h"

class Solution {
  public:
    int maxArea(vector<int> &height) {
        int left = 0, right = height.size() - 1;
        int answer = 0;

        while (left < right) {
            int area = (right - left) * min(height[left], height[right]);
            answer = max(answer, area);
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return answer;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("11", "height");
    testSuite.addTestCases({
        // Original test cases
        {
            49,
            {1, 8, 6, 2, 5, 4, 8, 3, 7},
        },
        {
            1,
            {1, 1},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maxArea, testSuite);
}
