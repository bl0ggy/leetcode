#include "common.h"

class Solution {
  public:
    // Helped with editorial
    string shortestCommonSupersequence(string str1, string str2) {
        int length1 = str1.length(); // rows
        int length2 = str2.length(); // cols
        vector<vector<int>> dp(length1 + 1, vector<int>(length2 + 1, 0));
        for (int row = 0; row <= length1; row++) {
            dp[row][0] = row;
        }
        for (int col = 0; col <= length2; col++) {
            dp[0][col] = col;
        }

        for (int row = 1; row <= length1; row++) {
            for (int col = 1; col <= length2; col++) {
                if (str1[row - 1] == str2[col - 1]) {
                    dp[row][col] = dp[row - 1][col - 1] + 1;
                } else {
                    dp[row][col] = min(dp[row - 1][col], dp[row][col - 1]) + 1;
                }
            }
        }

        string ans = "";
        int row = length1, col = length2;
        while (row > 0 && col > 0) {
            if (str1[row - 1] == str2[col - 1]) {
                ans += str1[row - 1];
                row--;
                col--;
            } else if (dp[row - 1][col] < dp[row][col - 1]) {
                ans += str1[row - 1];
                row--;
            } else {
                ans += str2[col - 1];
                col--;
            }
        }
        while (row > 0) {
            ans += str1[row - 1];
            row--;
        }
        while (col > 0) {
            ans += str2[col - 1];
            col--;
        }

        reverse(ans.begin(), ans.end());
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
