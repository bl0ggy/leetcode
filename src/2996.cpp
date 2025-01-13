#include "common.h"

class Solution {
  public:
    int missingInteger(vector<int> &nums) {
        int size = nums.size();
        int sum = nums[0], i = 1;
        while (i < size && nums[i - 1] + 1 == nums[i]) {
            sum += nums[i++];
        }
        sort(nums.begin(), nums.end());
        auto it = find(nums.begin(), nums.end(), sum);
        while (it != nums.end()) {
            sum++;
            it = find(nums.begin(), nums.end(), sum);
        }
        return sum;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Smallest mising integer", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            6,
            {1, 2, 3, 2, 5},
        },
        {
            15,
            {3, 4, 5, 1, 12, 14, 13},
        },
        // Submission test cases
        {
            30,
            {4, 5, 6, 7, 8, 8, 9, 4, 3, 2, 7},
        },
        {
            39,
            {38},
        },
        {
            38,
            {37, 1, 2, 9, 5, 8, 5, 2, 9, 4},
        },
        {
            47,
            {46, 8, 2, 4, 1, 4, 10, 2, 4, 10, 2, 5, 7, 3, 1},
        },
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::missingInteger, testSuite);
}
