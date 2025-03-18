#include "common.h"

class Solution {
  public:
    int longestNiceSubarray(vector<int> &nums) {
        int size = nums.size();
        int left = 0, right = 1, currentXor = nums[0];
        int longest = 0;

        while (right < size) {
            if ((currentXor & nums[right]) == 0) {
                currentXor = currentXor ^ nums[right];
                right++;
            } else {
                currentXor = currentXor ^ nums[left];
                longest = max(longest, right - left);
                left++;
            }
        }
        longest = max(longest, right - left);

        return longest;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Longest nice subarray", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {1, 3, 8, 48, 10},
        },
        {
            1,
            {3, 1, 5, 11, 13},
        },
        // Submission test cases
        {
            8,
            {84139415, 693324769, 614626365, 497710833, 615598711, 264, 65552, 50331652, 1, 1048576, 16384, 544, 270532608, 151813349, 221976871, 678178917, 845710321, 751376227, 331656525, 739558112, 267703680},
        },
        // My test cases
        {
            2,
            {0b1111, 0b0001, 0b0010},
        },
    });

    Main main;
    main.runTests(&Solution::longestNiceSubarray, testSuite);
}
