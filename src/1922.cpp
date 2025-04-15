#include "algorithms.h"
#include "common.h"

class Solution {
  public:
    int countGoodNumbers(long long n) {
        const int mod = 1000000007;
        long long odds = n / 2;
        long long evens = n - odds;
        return (modpow(5, evens, mod) * modpow(4, odds, mod)) % mod;
    }
};

int main() {
    TestSuite<int, long long> testSuite("1922", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            1,
        },
        {
            400,
            4,
        },
        {
            564908303,
            50,
        },
        // My test cases
        // Submission test cases
        {
            643535977,
            806166225460393,
        },
    });

    Main main;
    main.runTests(&Solution::countGoodNumbers, testSuite);
}
