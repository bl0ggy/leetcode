#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    int longestSquareStreak(vector<int> &nums) {
        // Longest streak: 2, 4, 8, 16, 256, 65536 -> 6
        // Square root of maximum value 10e5 is 316.2, so a streak require the value to be under 317
        unordered_set<int> unique(nums.begin(), nums.end());
        nums = vector<int>(unique.begin(), unique.end());
        sort(nums.begin(), nums.end());
        int maxCount = 0;
        auto globalNum = nums.begin();
        auto numsEnd = nums.end();
        unique.clear(); // Reuse to skip already processed values
        while (globalNum != numsEnd && *globalNum < 317) {
            auto num = globalNum;
            if (unique.count(*num)) {
                globalNum++;
                continue;
            }
            int count = 1;
            while (*num < 317 && (num = find(num + 1, numsEnd, (*num) * (*num))) != numsEnd) {
                count++;
            }
            maxCount = max(maxCount, count);
            if (maxCount == 6) { // Longest streak
                return 6;
            }
            globalNum++;
        }

        return maxCount <= 1 ? -1 : maxCount;
    }
};

int main() {
    // vector<int> input{{4, 3, 6, 16, 8, 2}};
    vector<int> input{3, 9, 81, 6561};
    // vector<int> input{2};
    int expectedCount = 15;

    auto start = chrono::system_clock::now();

    Solution solution;
    int count = solution.longestSquareStreak(input);

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "elapsed = " << elapsed.count() << "ms\n";
    cout << "count=" << count << "\n";
    assert(count == expectedCount);
}
