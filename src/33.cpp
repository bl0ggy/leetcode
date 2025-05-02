#include "common.h"

class Solution {
  public:
    int search(vector<int> &nums, int target) {
        int size = nums.size();
        int answer = -1;
        int left = 0, right = size - 1;

        while (nums[left] > nums[right] && right - left > 1) {
            int mid = (right + left) / 2;
            if (nums[mid] > nums[left]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if (nums[left] > nums[right]) {
            left += size;
            swap(left, right);
        }
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid % size] < target) {
                left = mid + 1;
            } else if (nums[mid % size] > target) {
                right = mid - 1;
            } else {
                return mid % size;
            }
        }

        return answer;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("33", "nums", "target");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {4, 5, 6, 7, 0, 1, 2},
            0,
        },
        {
            -1,
            {4, 5, 6, 7, 0, 1, 2},
            3,
        },
        {
            -1,
            {1},
            0,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::search, testSuite);
}
