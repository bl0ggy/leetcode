#include "common.h"

class Solution {
  public:
    int largestRectangleArea(vector<int> &heights) {
        int max = 0;
        int size = heights.size();
        stack<int> stack;

        for (int i = 0; i < size; i++) {
            while (stack.size() > 0 && heights[stack.top()] >= heights[i]) {
                int current = stack.top();
                stack.pop();

                int width = stack.size() == 0 ? i : i - stack.top() - 1;
                max = std::max(max, width * heights[current]);
            }

            stack.push(i);
        }

        while (stack.size()) {
            int current = stack.top();
            stack.pop();

            int width = stack.size() == 0 ? size : size - stack.top() - 1;
            max = std::max(max, width * heights[current]);
        }
        return max;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("largest rectangle", "histogram");
    testSuite.addTestCases({
        // Original test cases
        {
            10,
            {2, 1, 5, 6, 2, 3},
        },
        {
            4,
            {2, 4},
        },
        // My test cases
        {
            //                              //     _     _       _
            10,                             //   _| |  _| |_   _| |
            {1, 2, 3, 1, 2, 3, 2, 1, 2, 3}, // _|   |_|     |_|   |
        },                                  //|___________________|
    });

    Main main;
    main.runTests(&Solution::largestRectangleArea, testSuite);
}
