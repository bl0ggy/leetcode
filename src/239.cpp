#include "common.h"

class Solution {
  public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        int size = nums.size();
        vector<int> answer(size - k + 1);
        deque<int> queue;

        for (int i = 0; i < size; i++) {
            int num = nums[i];

            while (!queue.empty() && queue.back() < num) {
                queue.pop_back();
            }
            queue.push_back(num);

            if (i >= k && nums[i - k] == queue.front()) {
                queue.pop_front();
            }

            if (i >= k - 1) {
                answer[i - k + 1] = queue.front();
            }
        }

        return answer;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int> testSuite("239", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            {3, 3, 5, 5, 6, 7},
            {1, 3, -1, -3, 5, 3, 6, 7},
            3,
        },
        {
            {1},
            {1},
            1,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maxSlidingWindow, testSuite);
}
