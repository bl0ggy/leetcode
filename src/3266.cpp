#include "common.h"

class Solution {
    long long mod = 1e9 + 7;

  public:
    long long modpow(long long base, long long exp, long long modulus) {
        long long res = 1;
        base = base % modulus;
        if (base == 0)
            return 0;
        while (exp > 0) {
            if (exp & 1)
                res = (res * base) % modulus;
            exp = exp >> 1; // y = y/2
            base = (base * base) % modulus;
        }
        return res;
    }
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier) {
        if (multiplier == 1) {
            return nums;
        }

        size_t size = nums.size();
        long long maxValue = 0;
        priority_queue<pair<uint64_t, size_t>, vector<pair<uint64_t, size_t>>, greater<pair<uint64_t, size_t>>> sortedNums;
        for (int i = 0; i < nums.size(); i++) {
            if (maxValue < nums[i]) {
                maxValue = nums[i];
            }
            sortedNums.push({nums[i], i});
        }

        while (k > 0 && sortedNums.top().first * multiplier <= maxValue) {
            auto [value, index] = sortedNums.top();
            sortedNums.pop();
            sortedNums.push({value * multiplier, index});
            k--;
        }

        int rounds = k / size;
        int extra = k % size;
        vector<int> answer(size, 0);
        while (sortedNums.size() != 0) {
            auto num = sortedNums.top();
            sortedNums.pop();
            long long e = (num.first * modpow(multiplier, rounds + (extra > 0), mod)) % mod;
            answer[num.second] = e;
            extra--;
        }

        return answer;
    }
};

int main() {
    TestSuite<vector<int>, vector<int>, int, int> testSuite("final state", "values", "k", "multiplier");
    testSuite.addTestCases({
        // Original test cases
        {
            {8, 4, 6, 5, 6},
            {2, 1, 3, 5, 6},
            5,
            2,
        },
        {
            {999999307, 999999993},
            {100000, 2000},
            2,
            1000000,
        },
        // Submit test cases
        {
            {198168519},
            {161209470},
            56851412,
            39846,
        },
    });

    Main main;
    return main.runTests(&Solution::getFinalState, testSuite);
}
