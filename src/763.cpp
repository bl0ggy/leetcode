#include "common.h"
#include <ranges>

class Solution {
  public:
    vector<int> partitionLabels(string s) {
        int length = s.length();
        vector<pair<int, int>> letters(26, {-1, -1});
        for (int i = 0; i < length; i++) {
            auto &letter = letters[s[i] - 'a'];
            if (letter.first == -1) {
                letter.first = i;
            }
            letter.second = i;
        }

        sort(letters.begin(), letters.end());

        vector<int> sizes;
        int lastIndex = -1, index = 0;
        for (auto &l : letters | views::filter([](pair<int, int> &i) { return i.first >= 0; })) {
            if (index < l.first) {
                sizes.push_back(index - lastIndex);
                lastIndex = index;
            }
            index = max(index, l.second);
        }
        sizes.push_back(index - lastIndex);

        return sizes;
    }
};

int main() {
    TestSuite<vector<int>, string> testSuite("Partition labels", "s");
    testSuite.addTestCases({
        // Original test cases
        {
            {9, 7, 8},
            "ababcbacadefegdehijhklij",
        },
        {
            {10},
            "eccbbbbdec",
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::partitionLabels, testSuite);
}
