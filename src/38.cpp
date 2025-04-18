#include "common.h"

class Solution {
  public:
    string countAndSay(int n) {
        string ans = "1", tmp = "";
        while (--n) {
            int i = 0;
            while (i < ans.size()) {
                char c = ans[i];
                int count = 1;
                while ((++i) < ans.size() && ans[i] == c) {
                    count++;
                }
                tmp += to_string(count) + c;
            }
            ans = tmp;
            tmp = "";
        }
        return ans;
    }
};

int main() {
    TestSuite<string, int> testSuite("38", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            "1211",
            4,
        },
        {
            "1",
            1,
        },
        // My test cases
        {"", 30},
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::countAndSay, testSuite);
}
