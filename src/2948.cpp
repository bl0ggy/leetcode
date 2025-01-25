#include "common.h"

class Solution {
  public:
    // 2 pointers (brute force)
    // O(n^2)
    // Time limit exceeded
    // vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
    //     int size = nums.size();
    //
    //     for (int i = 0; i < size - 1; i++) {
    //         for (int j = i + 1; j < size; j++) {
    //             if (nums[j] < nums[i] && abs(nums[i] - nums[j]) <= limit) {
    //                 swap(nums[i], nums[j]);
    //                 j = i - 1;
    //             }
    //         }
    //     }
    //
    //     return nums;
    // }

    // Sorting + grouping
    // O(n * log(n)))
    vector<int> lexicographicallySmallestArray(vector<int> &nums, int limit) {
        int size = nums.size();
        if (size < 2) {
            return nums;
        }

        vector<int> sorted(nums.begin(), nums.end());
        sort(sorted.begin(), sorted.end());
        unordered_map<int, int> numToGroup;
        unordered_map<int, list<int>> groupToList;
        numToGroup[sorted[0]] = 0;
        groupToList[0] = list<int>({sorted[0]});

        for (int i = 1, g = 0; i < size; i++) {
            if (sorted[i] - sorted[i - 1] <= limit) {
                numToGroup[sorted[i]] = g;
                groupToList[g].push_back(sorted[i]);
            } else {
                g++;
                groupToList[g] = list<int>({sorted[i]});
                numToGroup[sorted[i]] = g;
            }
        }

        for (int i = 0; i < size; i++) {
            int num = nums[i];
            int g = numToGroup[num];
            auto &l = groupToList[g];
            nums[i] = l.front();
            l.pop_front();
        }

        return nums;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int> testSuite("Smallest array", "nums", "limit");
    testSuite.addTestCases({
        // Original test cases
        {
            {1, 3, 5, 8, 9},
            {1, 5, 3, 9, 8},
            2,
        },
        {
            {1, 6, 7, 18, 1, 2},
            {1, 7, 6, 18, 2, 1},
            3,
        },
        {
            {1, 7, 28, 19, 10},
            {1, 7, 28, 19, 10},
            3,
        },
        // Submission test cases
        {
            {5, 100, 14, 16, 30, 44, 45, 64, 83, 65},
            {5, 100, 44, 45, 16, 30, 14, 65, 83, 64},
            15,
        },
        {
            {3, 4, 23, 84, 34, 88, 44, 44, 15, 18},
            {4, 3, 23, 84, 34, 88, 44, 44, 18, 15},
            3,
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::lexicographicallySmallestArray, testSuite);
}
