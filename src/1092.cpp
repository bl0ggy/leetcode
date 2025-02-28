#include "common.h"

class Solution {
  public:
    string shortestCommonSupersequence(string str1, string str2) {
        string ans = "";

        string a = slide(str1, str2, false);
        string c = slide(str2, str1, false);
        string b = slide(str1, str2, true);
        string d = slide(str2, str1, true);

        ans = a.length() <= b.length() ? a : b;
        ans = ans.length() <= c.length() ? ans : c;
        ans = ans.length() <= d.length() ? ans : d;
        return ans;
    }

    // Slides str1 over str2
    string slide(string str1, string str2, bool reverse) {
        if (reverse) {
            std::reverse(str1.begin(), str1.end());
            std::reverse(str2.begin(), str2.end());
        }
        int length1 = str1.length(), length2 = str2.length();
        int p1 = 0, p2 = 0;
        pair<int, int> lastMatch = {-1, -1}; // p1,p2
        string ans = "";
        for (int startP1 = 0; lastMatch.second == -1 && startP1 < length1; startP1++) {
            p1 = startP1;
            p2 = 0;
            ans = str1.substr(0, startP1);
            while (p1 < length1 && lastMatch.second + 1 < length2) {
                bool match = str1[p1] == str2[p2];
                if (match) {
                    if (p1 > lastMatch.first + 1) {
                        ans += str1.substr(lastMatch.first + 1, p1 - (lastMatch.first + 1));
                    }
                    if (p2 > lastMatch.second + 1) {
                        ans += str2.substr(lastMatch.second + 1, p2 - (lastMatch.second + 1));
                    }
                    ans += str1[p1];
                    lastMatch.first = p1;
                    lastMatch.second = p2;
                    p1++;
                    p2++;
                } else {
                    p2++;
                }
                if (p1 < length1 && p2 == length2) {
                    if (!match) {
                        p1++;
                    }
                    p2 = lastMatch.second + 1;
                }
            }
        }

        if (lastMatch.second == -1) {
            return str1 + str2;
        }
        if (lastMatch.first + 1 < length1) {
            ans += str1.substr(lastMatch.first + 1);
        }
        if (lastMatch.second + 1 < length2) {
            ans += str2.substr(lastMatch.second + 1);
        }
        if (reverse) {
            std::reverse(ans.begin(), ans.end());
        }
        return ans;
    }
};

int main() {
    TestSuite<string, string, string> testSuite("Shortest string", "str1", "str2");
    testSuite.addTestCases({
        // Original test cases
        {
            "cabac",
            "abac",
            "cab",
        },
        {
            "aaaaaaaa",
            "aaaaaaaa",
            "aaaaaaaa",
        },
        // Submission test cases
        {
            "bbaabbbaaabb",
            "baabaaabb",
            "bbabbbaab",
        },
        // My test cases
        {
            "aczbd",
            "azb",
            "czd",
        },
        {
            "abczbc",
            "abcb",
            "bczbc",
        },
    });

    Main main;
    main.runTests(&Solution::shortestCommonSupersequence, testSuite);
}
