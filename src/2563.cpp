#include "common.h"

class Solution {
  public:
    long long countFairPairs(vector<int> &nums, int lower, int upper) {
        sort(nums.begin(), nums.end());
        return count(nums, upper) - count(nums, lower - 1);
    }

    long long count(vector<int> &nums, int num) {
        long long count = 0;
        int size = nums.size();
        int left = 0, right = size - 1;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum <= num) {
                count += right - left;
                left++;
            } else {
                right--;
            }
        }
        return count;
    }

    // Double loop, too slow
    // long long countFairPairs(vector<int> &nums, int lower, int upper) {
    //     auto numsBegin = nums.begin();
    //     auto numsEnd = nums.end();
    //     sort(numsBegin, numsEnd);
    //     int numsSize = nums.size();
    //     long long fairPairs = 0;
    //     for (int i = 0; i < numsSize - 1; i++) {
    //         for (int j = i + 1; j < numsSize; j++) {
    //             if (lower <= nums[i] + nums[j] && nums[i] + nums[j] <= upper) {
    //                 fairPairs++;
    //             }
    //         }
    //     }
    //
    //     return fairPairs;
    // }
};

int main() {
    TestSuite<long long, vector<int>, int, int> testSuite("# of fair pairs", "values", "lower", "upper");
    testSuite.addTestCases({
        // Original test cases
        {
            // {0,1,4,4,5,7}
            //
            6,
            {0, 1, 7, 4, 4, 5},
            3,
            6,
        },
        {
            1,
            {1, 7, 9, 2, 5},
            11,
            11,
        },
        // Submit test cases
        {
            0,
            {-1, 0},
            1,
            1,
        },
        // My test cases
        {
            // Pair with -3,9, then no pair for -2, then pairs again with 1,1,2,4
            6,
            {-3, -2, 1, 1, 2, 4, 9},
            3,
            6,
        },
    });

    Main main;
    return main.runTests(&Solution::countFairPairs, testSuite);
}
