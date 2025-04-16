#include "common.h"

class Solution {
  public:
    int countGoodTriplets(vector<int> &arr, int a, int b, int c) {
        int size = arr.size();
        int count = 0;

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                for (int k = j + 1; k < size; k++) {
                    if (abs(arr[i] - arr[j]) <= a && abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c) {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};

int main() {
    TestSuite<int, vector<int>, int, int, int> testSuite("1534", "arr", "a", "b", "c");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {3, 0, 1, 1, 9, 7},
            7,
            2,
            3,
        },
        {
            0,
            {1, 1, 2, 2, 3},
            0,
            0,
            1,
        },
        // My test cases
        // Submission test cases
        {
            12,
            {7, 3, 7, 3, 12, 1, 12, 2, 3}, // 7,3,7;
            5,
            8,
            1,
        },
    });

    Main main;
    main.runTests(&Solution::countGoodTriplets, testSuite);
}
