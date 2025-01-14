#include "common.h"

class Solution {
  public:
    // Brute force using set
    // string longestNiceSubstring(string s) {
    //     int length = s.length();
    //     int maxLength = 0;
    //     int maxLengthPos = -1;
    //     for (int i = 0; i < length - maxLength; i++) {
    //         unordered_set<char> charSet;
    //         bool newFound = false;
    //         for (int j = i; j < length; j++) {
    //             charSet.insert(s[j]);
    //             int size = j - i + 1;
    //             if (size > maxLength && check(charSet)) {
    //                 newFound = true;
    //                 maxLength = size;
    //                 maxLengthPos = i;
    //             }
    //         }
    //         if (newFound) {
    //             i += maxLength - 1;
    //         }
    //     }
    //
    //     return maxLength == 0 ? "" : s.substr(maxLengthPos, maxLength);
    // }
    //
    // bool check(unordered_set<char> &charSet) {
    //     for (auto c : charSet) {
    //         if ((c >= 'a' && !charSet.contains(c - 32)) || (c < 'a' && !charSet.contains(c + 32))) {
    //             return false;
    //         }
    //     }
    //     return true;
    // }

    // Brute force using bit mask
    string longestNiceSubstring(string s) {
        int length = s.length();
        int maxLength = 0;
        int maxLengthPos = -1;
        for (int i = 0; i < length - maxLength; i++) {
            int maskLower = 0, maskUpper = 0;
            bool newFound = false;
            for (int j = i; j < length; j++) {
                char c = s[j];
                if (c >= 'a') {
                    maskLower |= 1 << (c - 'a');
                } else {
                    maskUpper |= 1 << (c - 'A');
                }
                int size = j - i + 1;
                if (size > maxLength && (maskLower == maskUpper)) {
                    newFound = true;
                    maxLength = size;
                    maxLengthPos = i;
                }
            }
            if (newFound) {
                i += maxLength - 1;
            }
        }

        return maxLength == 0 ? "" : s.substr(maxLengthPos, maxLength);
    }
};

int main() {
    TestSuite<string, string> testSuite("Longest nice substring", "s");
    testSuite.addTestCases({
        // Original test cases
        {
            "aAa",
            "YazaAay",
        },
        {
            "Bb",
            "Bb",
        },
        {
            "",
            "c",
        },
        // Submission test cases
        {
            "ddD",
            "zUXxizubXNKAUGXTjmAXkpzNZMnRBgddDUAWPUa",
        },
        // My test cases
        {
            "aaaAAAaaa",
            "aaaAAAaaa",
        },
        {
            "bbBBbb",
            "bbBBbbzaaAAaa",
        },
    });

    Main main;
    return main.runTests(&Solution::longestNiceSubstring, testSuite);
}
