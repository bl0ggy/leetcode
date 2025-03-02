#include "common.h"

class Solution {
  public:
    vector<vector<int>> mergeArrays(vector<vector<int>> &nums1, vector<vector<int>> &nums2) {
        vector<vector<int>> ans;
        int size1 = nums1.size(), size2 = nums2.size();
        int p1 = 0, p2 = 0;
        while (p1 < size1 && p2 < size2) {
            int i1 = nums1[p1][0];
            int v1 = nums1[p1][1];
            int i2 = nums2[p2][0];
            int v2 = nums2[p2][1];
            if (i1 == i2) {
                ans.push_back({i1, v1 + v2});
                p1++;
                p2++;
            } else if (i1 < i2) {
                ans.push_back({i1, v1});
                p1++;
            } else {
                ans.push_back({i2, v2});
                p2++;
            }
        }
        while (p1 < size1) {
            ans.push_back(nums1[p1++]);
        }
        while (p2 < size2) {
            ans.push_back(nums2[p2++]);
        }

        return ans;
    }
};

int main() {
    TestSuite<vector<vector<int>>, vector<vector<int>>, vector<vector<int>>> testSuite("two sum", "values", "target");
    testSuite.addTestCases({
        // Original test cases
        {
            {{1, 6}, {2, 3}, {3, 2}, {4, 6}},
            {{1, 2}, {2, 3}, {4, 5}},
            {{1, 4}, {3, 2}, {4, 1}},
        },
        {
            {{1, 3}, {2, 4}, {3, 6}, {4, 3}, {5, 5}},
            {{2, 4}, {3, 6}, {5, 5}},
            {{1, 3}, {4, 3}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::mergeArrays, testSuite);
}
