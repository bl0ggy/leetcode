#include "common.h"

class Solution {
  public:
    // 2 pointers + recursion
    // Time limit exceeded
    // bool isMatch(string s, string p) {
    //     int l = 1, lastStarIndex = -1;
    //     while (l < p.size() && p.size() > 1) {
    //         if (p[l] == '*' && p[l] == p[l - 1]) {
    //             p.erase(l, 1);
    //             lastStarIndex = l;
    //         } else {
    //             l++;
    //         }
    //     }
    //
    //     int sSize = s.size();
    //     int pSize = p.size();
    //
    //     if (sSize == 0 && p == "*") {
    //         return true;
    //     }
    //
    //     int is = 0, ip = 0;
    //     return findMatch(s, p, is, sSize, ip, pSize, lastStarIndex);
    // }
    // bool findMatch(string s, string p, int is, int sSize, int ip, int pSize, int lastStarIndex) {
    //     while (is < sSize || ip < pSize) {
    //         if (p[ip] == '*') {
    //             if (ip == pSize - 1) {
    //                 return true;
    //             }
    //             if (ip == lastStarIndex) {
    //                 int i;
    //                 for (i = sSize - 1; i >= is; i--) {
    //                     if (p[ip + 1] == '?' || s[is] == p[ip + 1]) {
    //                         is = i;
    //                         ip++;
    //                         break;
    //                     }
    //                 }
    //                 if (i == is + 1) {
    //                     return false;
    //                 }
    //             } else {
    //                 int i;
    //                 for (i = is; i < sSize; i++) {
    //                     if (p[ip + 1] == '?' || s[i] == p[ip + 1]) {
    //                         if (findMatch(s, p, i + 1, sSize, ip + 2, pSize, lastStarIndex)) {
    //                             return true;
    //                         }
    //                     }
    //                 }
    //                 return false;
    //             }
    //         } else if (is < sSize && (p[ip] == '?' || p[ip] == s[is])) {
    //             ip++;
    //             is++;
    //         } else {
    //             return false;
    //         }
    //     }
    //     return is == sSize && ip == pSize;
    // }

    // DP
    bool isMatch(string s, string p) {
        int sSize = s.size();
        int pSize = p.size();
        vector<vector<int>> dp(sSize + 1, vector<int>(pSize + 1));
        dp[0][0] = true;

        for (int i = 1; i <= pSize; i++) {
            if (p[i - 1] == '*') {
                dp[0][i] = dp[0][i - 1];
            }
        }

        for (int i = 1; i <= sSize; i++) {
            for (int j = 1; j <= pSize; j++) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }

        return dp[sSize][pSize];
    }
};

int main() {
    TestSuite<bool, string, string> testSuite("Is match", "string", "pattern");
    testSuite.addTestCases({
        // Original test cases
        {
            false,
            "aa",
            "a",
        },
        {
            true,
            "aa",
            "*",
        },
        {
            false,
            "cb",
            "?a",
        },
        // Submission test cases
        {
            true,
            "adceb",
            "*a*b",
        },
        {
            true,
            "",
            "******",
        },
        {
            true,
            "abcabczzzde",
            "*abc???de*",
        },
        {
            true,
            "c",
            "*?*",
        },
        // My test cases
        {
            false,
            "",
            "**f****",
        },
        {
            true,
            "abcabc",
            "*abc",
        },
        {
            true,
            "abczzzde",
            "abc???de*",
        },
    });

    Main main;
    return main.runTests(&Solution::isMatch, testSuite);
}
