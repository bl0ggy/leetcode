#include "common.h"

class Solution {
  public:
    int lenLongestFibSubseq(vector<int> &arr) {
        int ans = 0;
        int size = arr.size();

        for (int prevI = 0; prevI < size - 1; prevI++) {
            for (int i = prevI + 1; i < size; i++) {
                int currentPrevI = prevI;
                int currentI = i;
                int next = currentI + 1;
                int count = 2;
                while (next < size) {
                    int toFind = arr[currentI] + arr[currentPrevI];
                    while (next < size && arr[next] < toFind) {
                        next++;
                    }
                    if (next < size && arr[next] == toFind) {
                        count++;
                        currentPrevI = currentI;
                        currentI = next;
                        next++;
                    } else {
                        break;
                    }
                }

                ans = max(ans, count > 2 ? count : 0);
            }
        }

        return ans;
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
