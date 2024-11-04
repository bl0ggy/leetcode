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
    const string nameInput1 = "nums";
    const string nameInput2 = "k";
    const string nameInput3 = "multiplier";
    const string nameOutput = "final state";
    vector<TestCase<vector<int>, int, int, vector<int>>> testCases{
        {
            {nameInput1, {161209470}},
            {nameInput2, 56851412},
            {nameInput3, 39846},
            {nameOutput, {198168519}},
        },
        {
            {nameInput1, {2, 1, 3, 5, 6}},
            {nameInput2, 5},
            {nameInput3, 2},
            {nameOutput, {8, 4, 6, 5, 6}},
        },
        {
            {nameInput1, {100000, 2000}},
            {nameInput2, 2},
            {nameInput3, 1000000},
            {nameOutput, {999999307, 999999993}},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<int>, int, int, vector<int>> testCase) {
        Solution solution;
        return solution.getFinalState(testCase.input1, testCase.input2, testCase.input3);
    });
}
