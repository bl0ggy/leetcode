#include "common.h"

class Solution {
  public:
    long long minimumTotalDistance(vector<int> &robots, vector<vector<int>> &factories) {
        sort(robots.begin(), robots.end());
        sort(factories.begin(), factories.end());
        vector<int> flattenedFactories;
        for (auto f : factories) {
            for (int i = 0; i < f[1]; i++) {
                flattenedFactories.push_back(f[0]);
            }
        }

        size_t robotsSize = robots.size();
        size_t factoriesSize = flattenedFactories.size();
        vector<vector<long long>> distances(robotsSize + 1, vector<long long>(factoriesSize + 1, 0));
        for (int i = 0; i < robotsSize; i++) {
            distances[i][factoriesSize] = 1e12;
        }
        for (size_t r = robotsSize - 1; r < INT_MAX; r--) {
            for (size_t f = factoriesSize - 1; f < INT_MAX; f--) {
                long long a = distances[r][f + 1];
                long long b = distances[r + 1][f + 1] + abs(robots[r] - flattenedFactories[f]);
                distances[r][f] = min(a, b);
            }
        }

        return distances[0][0];
    }
};

int main() {
    TestSuite<int, vector<int>, vector<vector<int>>> testSuite("minimum total distance", "robots", "factories");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            {0, 4, 6},
            {{2, 2}, {6, 2}},
        },
        {
            2,
            {1, -1},
            {{-2, 2}, {2, 1}},
        },
        // Submit test cases
        {
            582755368,
            {789300819, -600989788, 529140594, -592135328, -840831288, 209726656, -671200998},
            {{-865262624, 6}, {-717666169, 0}, {725929046, 2}, {449443632, 3}, {-912630111, 0}, {270903707, 3}, {-769206598, 2}, {-299780916, 4}, {-159433745, 5}, {-467185764, 3}, {849991650, 7}, {-292158515, 6}, {940410553, 6}, {258278787, 0}, {83034539, 2}, {54441577, 3}, {-235385712, 2}, {75791769, 3}},
        },
        // My test cases
        {
            // r--r------ //
            // -------f-f //
            13,
            {1, 4},
            {{8, 1}, {10, 1}},
        },
        {
            // -------r-r //
            // f--f------ //
            13,
            {8, 10},
            {{1, 1}, {4, 1}},
        },
        {
            // r------r-- //
            // ---f-----f //
            5,
            {1, 8},
            {{4, 1}, {10, 1}},
        },
        {
            // ---r-----r //
            // f------f-- //
            5,
            {4, 10},
            {{1, 1}, {8, 1}},
        },
        {
            // r--------r //
            // ---f---f-- //
            5,
            {1, 10},
            {{4, 1}, {8, 1}},
        },
        {
            // ---r---r-- //
            // f--------f //
            5,
            {4, 8},
            {{1, 1}, {10, 1}},
        },
    });

    Main main;
    return main.runTests(&Solution::minimumTotalDistance, testSuite);
}
