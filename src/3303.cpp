#include "common.h"
#include <map>

class Solution {
  private:
  public:
    // Sliding window
    // With n the length of s+pattern: O(n^2)
    // int minStartingIndex(std::string s, std::string pattern) {
    //     int maxErrors = 1;
    //     int sL = s.length();
    //     int pL = pattern.length();
    //     for (int i = 0; i < sL - pL + 1;) {
    //         vector<int> errors;
    //         int j = 0;
    //         for (; j < pL && errors.size() <= maxErrors; j++) {
    //             if (s[i + j] != pattern[j]) {
    //                 errors.push_back(i + j);
    //             }
    //         }
    //         int errs = errors.size();
    //         if (errs <= maxErrors) {
    //             return i;
    //         } else if (errs > maxErrors + 1) {
    //             i = errors[errs - 2]; // -2 because for loop does ++
    //         } else {
    //             i++;
    //         }
    //     }
    //     return -1;
    // }

    // [abc]
    // [abbacbabcba]
    // [abcabbacbabcba]
    // [30020010030001]
    //
    // [aaabaaabaaab]
    // [421042104210]
    // [43]

    // Z function
    // O(n)
    // Time exceeded? 770/778
    int minStartingIndex(std::string str, std::string pattern) {
        int maxErrors = 1;
        string s{pattern + str};
        int pL = pattern.length();
        int n = s.length();
        vector<int> z(n);
        for (int i = pL, l = 0, r = 0; i < n; i++) {
            int errors = 0;
            if (i <= r) {
                z[i] = min(z[i - l], r - i + 1);
            }
            while (i + z[i] < n && (s[z[i]] == s[i + z[i]] || errors < maxErrors)) {
                if (s[z[i]] != s[i + z[i]]) {
                    errors++;
                    if (errors < maxErrors) {
                        --z[i];
                    }
                }
                ++z[i];
            }
            if (z[i] >= pL) {
                return i - pL;
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }

        return -1;
    }

    // Z algorithm (2)
    // O(n)
    // Failed attempt
    // int minStartingIndex(std::string str, std::string pattern) {
    //     int maxErrors = 1;
    //     string s{pattern + str};
    //     int pL = pattern.length();
    //     int n = s.length();
    //     vector<int> z(n);
    //     for (int i = pL, l = pL - 1, r = pL - 1; i < n; i++) {
    //         cout << "i=" << i << " r=" << r << endl;
    //         int errors = 0;
    //         if (i >= r) {
    //             cout << "i>r" << endl;
    //             r = l = i;
    //             while (r < n && (s[r] == s[r - l] || errors < maxErrors)) {
    //                 cout << "l=" << l << " r=" << r << " s[r]=" << s[r] << " s[r - l]=" << s[r - l] << endl;
    //                 if (s[r] != s[r - l]) {
    //                     cout << "error" << endl;
    //                     errors++;
    //                 }
    //                 r++;
    //             }
    //             z[i] = r - l;
    //             cout << "er " << errors << endl;
    //             if (errors > maxErrors) {
    //                 --z[i];
    //                 r--;
    //             }
    //             r--;
    //         } else {
    //             cout << "i<r" << endl;
    //             int j = i - l;
    //             if (z[j] < r - j + 1) {
    //                 cout << "l=" << l << " r=" << r << " i=" << i << " j=" << j << " z[j]=" << z[j] << endl;
    //                 z[i] = z[j];
    //                 i--;
    //             } else {
    //                 l = i;
    //                 while (r < n && (s[r] == s[r - l] || errors < maxErrors)) {
    //                     cout << "r=" << r << " l=" << l << " s[r]=" << s[r] << " s[r - l]=" << s[r - l] << endl;
    //                     if (s[r] != s[r - l]) {
    //                         errors++;
    //                     }
    //                     r++;
    //                 }
    //                 z[i] = r - l;
    //                 if (errors < maxErrors) {
    //                     --z[i];
    //                 }
    //                 r--;
    //             }
    //         }
    //         cout << "l=" << l << " r=" << r << " " << toString(z) << endl;
    //         if (z[i] >= pL) {
    //             return i - pL;
    //         }
    //     }
    //     // cout << toString(z) << endl;
    //     return -1;
    // }
};

int main() {
    TestSuite<int, string, string> testSuite("index", "s", "pattern");
    testSuite.addTestCases({
        // Original test cases
        {
            1,
            "abcdefg",
            "bcdffg",
        },
        {
            4,
            "ababbababa",
            "bacaba",
        },
        {
            -1,
            "abcd",
            "dba",
        },
        {
            0,
            "dde",
            "d",
        },
        // Submission test cases
        {
            -1,
            "hhghhhhhhghhhgg",
            "ggghh",
        },
        {
            1,
            "dcdccdddcdcdddccddccccddcd",
            "ddc",
        },
        {
            3,
            "eeddddeddd",
            "ddee",
        },
        // My test cases
        {
            0,
            "aaabaaab",
            "aaab",
        },
    });

    Main main;
    return main.runTests(&Solution::minStartingIndex, testSuite);
}
