#include "common.h"

class Solution {
  public:
    vector<int> twoSum(vector<int> &nums, int target) {
        size_t numsSize = nums.size();
        unordered_map<int, int> numMap;
        for (int i = 0; i < numsSize; i++) {
            int numToFind = target - nums[i];
            if (numMap.count(numToFind)) {
                return {numMap[numToFind], i};
            }
            numMap[nums[i]] = i;
        }
        return {};
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int> testSuite("two sum", "values", "target");
    testSuite.addTestCases({
        {
            {0, 1},
            {2, 7, 11, 15},
            9,
        },
        {
            {1, 2},
            {3, 2, 4},
            6,
        },
        {
            {0, 1},
            {3, 3},
            6,
        },
    });

    Main main;
    main.runTests(&Solution::twoSum, testSuite);
}
