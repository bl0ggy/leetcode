#include "common.h"

class Solution {
  public:
    // Time limit exceeded
    // int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    //     int sizeNums = nums.size(), sizeQueries = queries.size();
    //     int left = 0;
    //     int queryIndex = 0;
    //
    //     while (left < sizeNums && nums[left] == 0) {
    //         left++;
    //     }
    //
    //     while (left < sizeNums && queryIndex < sizeQueries) {
    //         auto q = queries[queryIndex++];
    //         int l = q[0], r = q[1], v = q[2];
    //         for (int i = l; i <= r; i++) {
    //             nums[i] -= min(nums[i], v);
    //         }
    //         while (left < sizeNums && nums[left] == 0) {
    //             left++;
    //         }
    //     }
    //
    //     return left == sizeNums ? queryIndex : -1;
    // }

    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
        int sizeNums = nums.size();
        int sizeQueries = queries.size();
        int queryIndex = 0;
        vector<int> difference(sizeNums + 1);
        int sum = 0;

        for (int numIndex = 0; numIndex < sizeNums; numIndex++) {
            while (sum + difference[numIndex] < nums[numIndex]) {
                queryIndex++;
                if (queryIndex > sizeQueries) {
                    return -1;
                }

                auto q = queries[queryIndex - 1];
                int l = q[0], r = q[1], v = q[2];

                if (r >= numIndex) {
                    difference[max(l, numIndex)] += v;
                    difference[r + 1] -= v;
                }
            }
            sum += difference[numIndex];
        }

        return queryIndex;
    }
};

int main() {
    TestSuite<int, vector<int>, vector<vector<int>>> testSuite("Minimum queries", "nums", "queries");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {2, 0, 2},
            {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}},
        },
        {
            -1,
            {4, 3, 2, 1},
            {{1, 3, 2}, {0, 2, 1}},
        },
        // Submission test cases
        {
            4,
            {7, 6, 8},
            {{0, 0, 2}, {0, 1, 5}, {2, 2, 5}, {0, 2, 4}},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minZeroArray, testSuite);
}
