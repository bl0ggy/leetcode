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
    const string nameInput1 = "robots";
    const string nameInput2 = "factories";
    const string nameOutput = "minimum total distance";
    vector<TestCase<vector<int>, vector<vector<int>>, int>> testCases{
        {
            {nameInput1, {0, 4, 6}},
            {nameInput2, {{2, 2}, {6, 2}}},
            {nameOutput, 4},
        },
        {
            {nameInput1, {1, -1}},
            {nameInput2, {{-2, 2}, {2, 1}}},
            {nameOutput, 2},
        },
        {
            // r--r------ //
            // -------f-f //
            {nameInput1, {1, 4}},
            {nameInput2, {{8, 1}, {10, 1}}},
            {nameOutput, 13},
        },
        {
            // -------r-r //
            // f--f------ //
            {nameInput1, {8, 10}},
            {nameInput2, {{1, 1}, {4, 1}}},
            {nameOutput, 13},
        },
        {
            // r------r-- //
            // ---f-----f //
            {nameInput1, {1, 8}},
            {nameInput2, {{4, 1}, {10, 1}}},
            {nameOutput, 5},
        },
        {
            // ---r-----r //
            // f------f-- //
            {nameInput1, {4, 10}},
            {nameInput2, {{1, 1}, {8, 1}}},
            {nameOutput, 5},
        },
        {
            // r--------r //
            // ---f---f-- //
            {nameInput1, {1, 10}},
            {nameInput2, {{4, 1}, {8, 1}}},
            {nameOutput, 5},
        },
        {
            // ---r---r-- //
            // f--------f //
            {nameInput1, {4, 8}},
            {nameInput2, {{1, 1}, {10, 1}}},
            {nameOutput, 5},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<int>, vector<vector<int>>, int> testCase) {
        Solution solution;
        return solution.minimumTotalDistance(testCase.input1, testCase.input2);
    });
}
