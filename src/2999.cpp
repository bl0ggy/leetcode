#include "common.h"

class Solution {
  public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string startStr = to_string(start - 1);
        string finishStr = to_string(finish);
        return calculate(finishStr, s, limit) - calculate(startStr, s, limit);
    }
    long long calculate(string &x, string &s, int limit) {
        if (x.length() < s.length()) {
            return 0;
        }
        if (x.length() == s.length()) {
            return x < s ? 0 : 1;
        }

        int diffLength = x.length() - s.length();
        long long ans = 0;

        for (int i = 0; i < diffLength; i++) {
            if ((x[i] - '0') > limit) {
                ans += pow<long long>(limit + 1, diffLength - i);
                return ans;
            }
            ans += (x[i] - '0') * pow<long long>(limit + 1, diffLength - i - 1);
        }

        if (x.substr(diffLength) >= s) {
            ans++;
        }

        return ans;
    }
};

int main() {
    TestSuite<long long, long long, long long, int, string> testSuite("2999", "start", "finish", "limit", "s");
    testSuite.addTestCases({
        // Original test cases
        {
            5,
            1,
            6000,
            4,
            "124",
        },
        {
            2,
            15,
            215,
            6,
            "10",
        },
        {
            0,
            1000,
            2000,
            4,
            "3000",
        },
        // My test cases
        {
            24,
            1234,
            5234,
            5,
            "25",
        },
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::numberOfPowerfulInt, testSuite);
}
