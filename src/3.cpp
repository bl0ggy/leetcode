#include "common.h"
#include <set>

class Solution {
  public:
    int lengthOfLongestSubstring(string s) {
        size_t length = s.length();
        if (length < 2) {
            return length;
        }

        // 2 pointers with manual over over previous elements
        // int result = 1;
        // int i, j, k;
        // for (i = 0; i < length - 1; i++) {
        //     bool repeat;
        //     for (j = i + 1, repeat = false; !repeat && j < length; j++) {
        //         for (k = i; k < j; k++) {
        //             if (s[k] == s[j]) {
        //                 repeat = true;
        //                 break;
        //             }
        //         }
        //         if (k == j) {
        //             result = max(result, k - i + 1);
        //         }
        //     }
        // }

        // 2 pointers with set
        int result = 0;
        set<char> set;
        for (int l = 0, r = 0; r < length; r++) {
            while (set.contains(s[r])) {
                set.erase(s[l++]);
            }
            set.insert(s[r]);
            result = max(result, r - l + 1);
        }

        return result;
    }
};

int main() {
    TestSuite<int, string> testSuite("longest substring", "string");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            "abcabcbb",
        },
        {
            1,
            "bbbbb",
        },
        {
            3,
            "pwwkew",
        },
        // Submission test cases
        {
            2,
            "au",
        },
        {
            2,
            "aab",
        },
        {
            3,
            "dvdf",
        },
    });

    Main main;
    return main.runTests(&Solution::lengthOfLongestSubstring, testSuite);
}
