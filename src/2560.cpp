#include "common.h"

class Solution {
  public:
    // Fails in the cases when we must not start on the first (sorted) element
    // int minCapability(vector<int> &nums, int k) {
    //     // minCapability cannot be under the k-th lowest value
    //     // since for each set of robbed house, we must take the maximum value
    //     int sizeNums = nums.size();
    //     vector<pair<int, int>> coloredNums(sizeNums); // vaue, index
    //     for (int i = 0; i < sizeNums; i++) {
    //         coloredNums[i] = {nums[i], i};
    //     }
    //     sort(coloredNums.begin(), coloredNums.end(), [](pair<int, int> a, pair<int, int> b) { return a.first < b.first || a.second < b.second; });
    //
    //     int currentIndex = 0;
    //     unordered_map<int, bool> visited;
    //     return findMin(coloredNums, visited, k, currentIndex);
    // }
    // int findMin(vector<pair<int, int>> &coloredNums, unordered_map<int, bool> &visited, int k, int currentIndex) {
    //     visited[coloredNums[currentIndex].second] = true;
    //     k--;
    //     if (k == 0) {
    //         return coloredNums[currentIndex].first;
    //     }
    //
    //     int minimumCapability = INT_MAX;
    //     if (k >= 1) {
    //         currentIndex++;
    //         while (visited[coloredNums[currentIndex].second - 1] || visited[coloredNums[currentIndex].second + 1]) {
    //             currentIndex++;
    //         }
    //         minimumCapability = min(minimumCapability, findMin(coloredNums, visited, k, currentIndex));
    //         while (coloredNums[currentIndex + 1].first == coloredNums[currentIndex].first) {
    //             currentIndex++;
    //             while (visited[coloredNums[currentIndex].second - 1] || visited[coloredNums[currentIndex].second + 1]) {
    //                 currentIndex++;
    //             }
    //             minimumCapability = min(minimumCapability, findMin(coloredNums, visited, k, currentIndex));
    //         }
    //     }
    //
    //     visited[currentIndex] = false;
    //     return minimumCapability;
    // }

    int minCapability(vector<int> &nums, int k) {
        int sizeNums = nums.size();
        int minValue = 1, maxValue = *max_element(nums.begin(), nums.end());

        while (minValue < maxValue) {
            int robbedHouses = 0;
            int mid = (minValue + maxValue) / 2;

            for (int i = 0; i < sizeNums; i++) {
                if (nums[i] <= mid) {
                    robbedHouses++;
                    i++;
                }
            }

            if (robbedHouses >= k) {
                maxValue = mid;
            } else {
                minValue = mid + 1;
            }
        }

        return minValue;
    }
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("Minimum capability", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {2, 3, 5, 9},
            2,
        },
        {
            2,
            {2, 7, 9, 3, 1},
            2,
        },
        // Submission test cases
        // My test cases
        {
            3,
            {1, 2, 3, 4, 5, 6, 7, 8},
            2,
        },
        {
            5,
            {1, 2, 3, 4, 5, 6, 7, 8},
            3,
        },
        {
            7,
            {1, 2, 3, 4, 5, 6, 7, 8},
            4,
        },
        {
            2,
            {1, 3, 5, 7, 2, 4, 6, 8},
            2,
        },
        {
            5,
            {1, 3, 5, 7, 2, 4, 6, 8},
            3,
        },
        {
            6,
            {1, 3, 5, 7, 2, 4, 6, 8}, // 1 2 5 6
            4,
        },
        {
            3,
            {3, 5, 7, 1, 2, 4, 6, 8},
            2,
        },
        {
            4,
            {3, 5, 7, 1, 2, 4, 6, 8},
            3,
        },
        {
            7,
            {3, 5, 7, 1, 2, 4, 6, 8}, // 1 3 4 7
            4,
        },
        {
            4,
            {3, 3, 5, 7, 1, 1, 2, 2, 4, 6, 8},
            4,
        },
    });

    Main main;
    main.runTests(&Solution::minCapability, testSuite);
}
