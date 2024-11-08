#include "common.h"

class Solution {
  public:
    vector<int> mostVisited(int n, vector<int> &rounds) {
        vector<int> answer;

        int startingSection = rounds[0];
        vector<int> sections(n);
        sections[0] = startingSection;
        for (int i = 1; i < n; i++) {
            if (sections[i - 1] == n) {
                sections[i] = 1;
            } else {
                sections[i] = sections[i - 1] + 1;
            }
        }
        int totalSectionsStepped = 0;
        for (int i = 1; i < rounds.size(); i++) {
            if (rounds[i] == rounds[i - 1]) {
                totalSectionsStepped += n;
            } else if (rounds[i] > rounds[i - 1]) {
                totalSectionsStepped += rounds[i] - rounds[i - 1];
            } else {
                totalSectionsStepped += rounds[i] + n - rounds[i - 1];
            }
        }

        int remaining = (totalSectionsStepped % n);
        if (remaining == n) {
            return rounds;
        }

        sections.erase(sections.begin() + remaining + 1, sections.end());
        sort(sections.begin(), sections.end());

        return sections;
    }
};

int main() {
    TestSuite<vector<int>, int, vector<int>> testSuite("most visited sections", "rounds", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            {2},                         //
            2,                           //
            {2, 1, 2, 1, 2, 1, 2, 1, 2}, //
        },
        {
            {1, 2},       //
            4,            //
            {1, 3, 1, 2}, //
        },
        {
            {1, 2, 3, 4, 5, 6, 7}, //
            7,                     //
            {1, 3, 5, 7},          //
        },
    });

    Main main;
    return main.runTests(&Solution::mostVisited, testSuite);
}
