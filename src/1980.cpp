#include "common.h"

class Solution {
  public:
    string findDifferentBinaryString(vector<string> &nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        if (find(nums.front().begin(), nums.front().end(), '1') != nums.front().end()) {
            return string(n, '0');
        }

        if (find(nums.back().begin(), nums.back().end(), '0') != nums.back().end()) {
            return string(n, '1');
        }

        int i = 0;
        string a = nums[i];
        do {
            add(a);
            i++;
        } while (a == nums[i]);
        return a;
    }

    bool add(string &s) {
        int l = s.length();
        int i = l - 1;

        // Increment
        s[i]++;
        while (s[i] > '1') {
            s[i] = '0';
            if (i == 0) {
                return false;
            }
            s[i - 1]++;
            i--;
        }

        // Reached '11...1'
        if (i == 0 && s[i] > '1') {
            return false;
        }
        return true;
    }
};

int main() {
    TestSuite<string, vector<string>> testSuite("Binary string", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            "11",
            {"01", "10"},
        },
        {
            "11",
            {"00", "01"},
        },
        {
            "101",
            {"111", "011", "001"},
        },
        // Submission test cases
        // My test cases
        {
            "011",
            {"000", "001", "010"},
        },
        {
            "000",
            {"101", "110", "111"},
        },
        {
            "010",
            {"000", "001", "111"},
        },
    });

    auto validationFunction = [](TestCase<string, vector<string>> &testCase) -> bool {
        auto v = get<0>(testCase.getInputs());
        return find(v.begin(), v.end(), testCase.returnedOutput) == v.end();
    };

    Main main;
    main.runTests(&Solution::findDifferentBinaryString, testSuite, validationFunction);
}
