#include "common.h"

class Solution {
  public:
    int minOperations(vector<int> &nums, int k) {
        int size = nums.size();
        sort(nums.begin(), nums.end(), greater<>());

        if (nums.back() < k) {
            return -1;
        }
        if (nums.front() == k) {
            return 0;
        }

        int count = 1;
        int current = nums.front();
        int i = 1;
        while (i < size && nums[i] > k) {
            if (nums[i] < current) {
                count++;
                current = nums[i];
            }
            i++;
        }

        return count;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("3375", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {5, 2, 5, 4, 5},
            2,
        },
        {
            -1,
            {2, 1, 2},
            2,
        },
        {
            4,
            {9, 7, 5, 3},
            1,
        },
        // My test cases
        {
            3,
            {5, 4, 3},
            2,
        },
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::minOperations, testSuite);
}
