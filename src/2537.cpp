#include "common.h"

class Solution {
  public:
    long long countGood(vector<int> &nums, int k) {
        long long count = 0;
        int size = nums.size();
        unordered_map<int, pair<int, int>> numCount; // value,(quantity,pairs)
        int satisfiedK = 0;
        int left = 0, right = 0;

        while (left < size) {
            if (right < size && satisfiedK < k) {
                satisfiedK += numCount[nums[right]].first;
                numCount[nums[right]].second += numCount[nums[right]].first;
                numCount[nums[right]].first++;
                right++;
            } else if (satisfiedK >= k) {
                numCount[nums[left]].first--;
                numCount[nums[left]].second -= numCount[nums[left]].first;
                satisfiedK -= numCount[nums[left]].first;
                left++;
            } else {
                break;
            }
            if (satisfiedK >= k) {
                count += 1 + size - right;
            }
        }

        return count;
    }
};

int main() {
    TestSuite<long long, vector<int>, int> testSuite("2537", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            1,
            {1, 1, 1, 1, 1},
            10,
        },
        {
            4,
            {3, 1, 4, 3, 2, 2, 4},
            2,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countGood, testSuite);
}
