#include "common.h"

class Solution {
  public:
    vector<int> largestDivisibleSubset(vector<int> &nums) {
        int size = nums.size();
        if (size == 1) {
            return nums;
        }

        sort(nums.begin(), nums.end());
        set<int> ans;
        for (int i = 0; i < size - 1; i++) {
            set<int> current{nums[i]};
            recurse(nums, i, current, ans);
        }

        return vector<int>(ans.begin(), ans.end());
    }

    void recurse(vector<int> &nums, int index, set<int> &current, set<int> &ans) {
        if (index >= nums.size()) {
            if (current.size() > ans.size()) {
                ans = current;
            }
            return;
        }

        // Skip
        recurse(nums, index + 1, current, ans);

        // Add if % = 0
        int num = nums[index];
        for (auto n : current) {
            if ((n % num) * (num % n) != 0) {
                return;
            }
        }
        current.insert(nums[index]);
        recurse(nums, index + 1, current, ans);
        current.erase(nums[index]);
    }
};

int main() {
    TestSuite<vector<int>, vector<int>> testSuite("Largest divisible subset", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            {1, 2},
            {1, 2, 3},
        },
        {
            {1, 2, 4, 8},
            {1, 2, 4, 8},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::largestDivisibleSubset, testSuite);
}
