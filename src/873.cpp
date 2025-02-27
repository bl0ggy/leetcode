#include "common.h"

class Solution {
  public:
    int lenLongestFibSubseq(vector<int> &arr) {
        int ans = 0;
        int size = arr.size();
        for (int i = 0; i < size; i++) {
            ans = max(ans, recurse(arr, 1, i));
        }

        return ans;
    }

    int recurse(vector<int> &arr, int count, int i, int prevI = -1) {
        int size = arr.size();
        if (prevI == -1) {
            int ans = 0;
            for (int nextI = i + 1; nextI < size; nextI++) {
                ans = max(ans, recurse(arr, count + 1, nextI, i));
            }
            return ans;
        }

        if (prevI + 1 < size) {
            int toFind = arr[i] + arr[prevI];
            for (int k = i + 1; k < size; k++) {
                if (arr[k] == toFind) {
                    return recurse(arr, count + 1, k, i);
                }
                if (arr[k] > toFind) {
                    break;
                }
            }
        }

        return count > 2 ? count : 0;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Longest fibonacci subsequence", "arr");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            {1, 2, 3, 4, 5, 6, 7, 8},
        },
        {
            3,
            {1, 3, 7, 11, 12, 14, 18},
        },
        // Submission test cases
        {
            5,
            {2, 4, 7, 8, 9, 10, 14, 15, 18, 23, 32, 50},
        }
        // My test cases
    });

    Main main;
    main.runTests(&Solution::lenLongestFibSubseq, testSuite);
}
