#include "algorithms.h"
#include "common.h"

class Solution {
  public:
    int maximumScore(vector<int> &nums, int k) {
        const long long MOD = 1e9 + 7;
        int n = nums.size();
        int maxelem = *max_element(nums.begin(), nums.end());

        auto primes = sieveOfEratosthenes(maxelem);

        vector<int> numsPrimes(n, 0);
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (primes[num]) {
                numsPrimes[i] = 1;
                continue;
            }
            for (int prime = 2; prime <= sqrt(num); prime++) {
                if (num % prime == 0) {
                    numsPrimes[i]++;
                    while (num % prime == 0) {
                        num /= prime;
                    }
                }
                while (!primes[prime + 1]) {
                    prime++;
                }
            }
            if (primes[num]) {
                numsPrimes[i]++;
            }
        }

        vector<int> previousDominant(n, -1), nextDominant(n, n);
        stack<int> dominants;
        for (int i = 0; i < n; i++) {
            while (!dominants.empty() && numsPrimes[i] > numsPrimes[dominants.top()]) {
                int top = dominants.top();
                dominants.pop();
                nextDominant[top] = i;
            }

            if (!dominants.empty()) {
                previousDominant[i] = dominants.top();
            }

            dominants.push(i);
        }

        vector<pair<int, long long>> sortedNums(n, {0, 0});
        for (int i = 0; i < n; i++) {
            sortedNums[i] = {nums[i], (long long)(i - previousDominant[i]) * (nextDominant[i] - i)};
        }
        sort(sortedNums.begin(), sortedNums.end(), greater<>());

        long long maxScore = 1;
        int index = 0;
        while (k > 0) {
            auto [num, windows] = sortedNums[index];
            long long mp = modpow(num, min(windows, (long long)k), MOD);
            maxScore = (maxScore * mp) % MOD;
            k -= windows;
            index++;
        }

        return maxScore;
    }

    int countPrimes(int num, vector<bool> &primes) {
        int count = 0;
        int prime = 2;
        while (prime < primes.size() && num > 1) {
            bool found = false;
            while (num % prime == 0) {
                num /= prime;
                found = true;
            }
            if (found) {
                count++;
            }
            prime++;
            while (prime < primes.size() && !primes[prime]) {
                prime++;
            }
        }
        return count;
    }

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
};

int main() {
    TestSuite<int, vector<int>, int> testSuite("Maximum score", "nums", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            81,
            {8, 3, 9, 3, 8},
            2,
        },
        {
            4788,
            {19, 12, 14, 6, 10, 18},
            3,
        },
        // Submission test cases
        {
            256720975,
            {3289, 2832, 14858, 22011},
            6,
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumScore, testSuite);
}
