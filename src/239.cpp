#include "common.h"

class Solution {
  public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k) {
        int size = nums.size();
        vector<int> answer(size - k + 1);
        map<int, int> values;
        for (int i = 0; i < k; i++) {
            values[nums[i]]++;
        }
        for (int i = k; i < size; i++) {
            answer[i - k] = values.rbegin()->first;
            values[nums[i - k]]--;
            values[nums[i]]++;
            if (values[nums[i - k]] == 0) {
                values.erase(nums[i - k]);
            }
        }
        answer[size - k] = values.rbegin()->first;
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
