#include "common.h"

class Solution {
  public:
    string getHappyString(int n, int k) {
        string ans(n, 'a');
        // Happify first string
        for (int i = 1; i < n; i += 2) {
            ans[i]++;
        }

        bool v;
        for (; k > 1; k--) {
            v = add(ans);
            if (!v) {
                return "";
            }
        }

        return ans;
    }

    bool add(string &s) {
        int l = s.length();
        int i = l - 1;

        // Increment
        s[i]++;
        while (i > 0 && s[i] > 'c') {
            s[i] = 'a';
            s[i - 1]++;
            i--;
        }

        // Reached 'cc...c'
        if (i == 0 && s[i] > 'c') {
            return false;
        }

        // Check unhappiness and recurse
        for (i = max(0, i - 1); i < l - 1; i++) {
            while (s[i] == s[i + 1]) {
                if (!add(s)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    TestSuite<string, int, int> testSuite("Happy string", "n", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            "c",
            1,
            3,
        },
        {
            "",
            1,
            4,
        },
        {
            "cab",
            3,
            9,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::getHappyString, testSuite);
}
