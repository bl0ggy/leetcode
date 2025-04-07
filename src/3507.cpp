#include "common.h"

class Solution {
  public:
    int minimumPairRemoval(vector<int> &nums) {
        int size = nums.size();
        vector<int> sums(size - 1);
        for (int i = 0; i < size - 1; i++) {
            sums[i] = nums[i] + nums[i + 1];
        }

        int ans = 0;
        while (true) {
            int i = 0;
            for (; i < nums.size() - 1; i++) {
                if (nums[i] > nums[i + 1]) {
                    break;
                }
            }
            if (i >= nums.size() - 1) {
                return ans;
            }

            auto it = min_element(sums.begin(), sums.end());
            int indexLowest = it - sums.begin();
            nums.erase(nums.begin() + indexLowest);
            nums[indexLowest] = *it;
            sums.erase(it);
            if (indexLowest - 1 >= 0) {
                sums[indexLowest - 1] = nums[indexLowest - 1] + nums[indexLowest];
            }
            if (indexLowest < sums.size()) {
                sums[indexLowest] = nums[indexLowest] + nums[indexLowest + 1];
            }
            ans++;
        }
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Minimum pair removal", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {5, 2, 3, 1},
        },
        {
            0,
            {1, 2, 2},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minimumPairRemoval, testSuite);
}
