#include "common.h"

class Solution {
  public:
    pair<vector<int>, vector<int>> findLengths(vector<int> &vec) {
        size_t size = vec.size();
        pair<vector<int>, vector<int>> sizes(vector<int>(size, 1), vector<int>(size, 1));
        vector<int> accumulatorIncreasing = {vec[0]};
        vector<int> accumulatorDecreasing = {vec[size - 1]};
        for (int i = 1; i < size; i++) {
            auto indexIncreasing = lower_bound(accumulatorIncreasing.begin(), accumulatorIncreasing.end(), vec[i]) - accumulatorIncreasing.begin();
            if (indexIncreasing == accumulatorIncreasing.size()) {
                accumulatorIncreasing.push_back(vec[i]);
            } else {
                accumulatorIncreasing[indexIncreasing] = vec[i];
            }
            sizes.first[i] = accumulatorIncreasing.size();

            auto indexDecreasing = lower_bound(accumulatorDecreasing.begin(), accumulatorDecreasing.end(), vec[size - 1 - i]) - accumulatorDecreasing.begin();
            if (indexDecreasing == accumulatorDecreasing.size()) {
                accumulatorDecreasing.push_back(vec[size - 1 - i]);
            } else {
                accumulatorDecreasing[indexDecreasing] = vec[size - 1 - i];
            }
            sizes.second[i] = accumulatorDecreasing.size();
        }

        return sizes;
    }

    int minimumMountainRemovals(vector<int> &vec) {
        size_t size = vec.size();
        auto lengths = findLengths(vec);
        int minRemovals = INT_MAX;
        for (int i = 0; i < size; i++) {
            if (lengths.first[i] < 2 || lengths.second[size - 1 - i] < 2) {
                continue;
            }
            minRemovals = min(minRemovals, (int)size + 1 - (lengths.first[i] + lengths.second[size - 1 - i]));
        }

        return minRemovals;
    }
};

int main() {
    const string nameInput = "word";
    const string nameOutput = "minimum mountain removals";
    vector<TestCase<vector<int>, int>> testCases{
        {
            {nameInput, {1, 3, 1}},
            {nameOutput, 0},
        },
        {
            {nameInput, {2, 1, 1, 5, 6, 2, 3, 1}}, // length: 8
            {nameOutput, 3},
        },
        {
            // Randoms drops
            {nameInput, {1, 2, 3, 1, 4, 5, 1, 6, 1, 4, 1}}, // length: 11
            {nameOutput, 3},
        },
        {
            // Succinct drops
            {nameInput, {1, 2, 3, 1, 1, 1, 1, 4, 5, 6, 4, 1}}, // length = 12
            {nameOutput, 4},
        },
        {
            // Repeating sequences
            {nameInput, {1, 2, 3, 1, 2, 3, 1, 2, 3, 5, 6, 4, 1}}, // length = 13
            {nameOutput, 6},
        },
        {
            // Starting from the maximum is incorrect
            {nameInput, {1, 2, 3, 4, 5, 4, 3, 2, 6, 1}}, // length = 10
            {nameOutput, 1},
        },
        {
            // Starting from the minimum is incorrect
            {nameInput, {4, 5, 6, 1, 5, 4, 3}}, // length = 7
            {nameOutput, 1},
        },
        {
            // Start with highest number
            {nameInput, {9, 8, 1, 7, 6, 5, 4, 3, 2, 1}}, // length = 10
            {nameOutput, 2},
        },
        {
            {nameInput, {4, 5, 13, 17, 1, 7, 6, 11, 2, 8, 10, 15, 3, 9, 12, 14, 16}}, // length = 17
            {nameOutput, 10},
        },
    };

    Main main;
    return main.runTests(testCases, [](TestCase<vector<int>, int> testCase) {
        Solution solution;
        return solution.minimumMountainRemovals(testCase.input);
    });
}
