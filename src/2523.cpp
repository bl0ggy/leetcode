#include "common.h"

class Solution {
  public:
    vector<int> closestPrimes(int left, int right) {
        vector<pair<int, int>> primes(right + 1, {0, 0}); // number,mark(0:not marked,1:prime,2:not prime)
        primes[0].second = 2;
        primes[1].second = 2;
        for (int i = 2; i <= right; i++) {
            primes[i] = {i, 0};
        }
        for (auto &[val, mark] : primes) {
            if (mark == 0) {
                mark = 1;
                for (unsigned long j = (unsigned long)val * val; j <= right; j += val) {
                    primes[j].second = 2;
                }
            }
        }

        int minDiff = INT_MAX;
        int lastPrime = -1;
        vector<int> adjPrimes{0, INT_MAX};
        int i = left;
        for (; i <= right; i++) {
            if (primes[i].second == 1) {
                lastPrime = i;
                i++;
                break;
            }
        }
        for (; i <= right; i++) {
            if (primes[i].second == 1) {
                int diff = i - lastPrime;
                if (diff < minDiff) {
                    adjPrimes[0] = lastPrime;
                    adjPrimes[1] = i;
                    minDiff = diff;
                }
                lastPrime = i;
            }
        }
        if (adjPrimes[1] == INT_MAX) {
            return {-1, -1};
        }
        return adjPrimes;
    }
};

int main() {
    TestSuite<vector<int>, int, int> testSuite("Closest primes", "left", "right");
    testSuite.addTestCases({
        // Original test cases
        {
            {11, 13},
            10,
            19,
        },
        {
            {-1, -1},
            4,
            6,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::closestPrimes, testSuite);
}
