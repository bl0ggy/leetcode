#include "common.h"

class Solution {
  public:
    int countDays(int days, vector<vector<int>> &meetings) {
        sort(meetings.begin(), meetings.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0] || (a[1] == b[1] && a[1] < b[1]) || false; });
        cout << toString(meetings) << endl;
        int currentDay = 0;
        int dayCount = 0;
        for (int i = 0; i < meetings.size(); i++) {
            auto &meeting = meetings[i];
            if (currentDay < meeting[0]) {
                dayCount += meeting[0] - currentDay - 1;
                currentDay = meeting[1];
            } else if (currentDay < meeting[1]) {
                currentDay = meeting[1];
            }
        }

        if (days > currentDay) {
            dayCount += days - currentDay;
        }

        return dayCount;
    }
};

int main() {
    TestSuite<int, int, vector<vector<int>>> testSuite("Number of days", "days", "meetings");
    testSuite.addTestCases({
        // Original test cases
        {
            // |--------|
            // ---
            //     ---
            //         --
            //    o   o
            //
            2,
            10,
            {{5, 7}, {1, 3}, {9, 10}},
        },
        {
            // |---|
            // ---
            //  ---
            //     o
            1,
            5,
            {{2, 4}, {1, 3}},
        },
        {
            // |----|
            // ------
            0,
            6,
            {{1, 6}},
        },
        // Submission test cases
        {
            0,
            24,
            {{21, 24}, {9, 18}, {6, 20}, {8, 21}, {14, 24}, {19, 24}, {13, 21}, {1, 23}, {13, 24}, {7, 18}},
        },
        // My test cases
        {
            // |------------|
            //   ---
            //    ---
            //          ---
            //         ---
            6,
            14,
            {{3, 5}, {4, 6}, {9, 11}, {10, 12}},
        },
    });

    Main main;
    main.runTests(&Solution::countDays, testSuite);
}
