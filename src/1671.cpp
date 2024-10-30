#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

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

    void print(vector<int> vec) {
        for (int val : vec) {
            cout << val << " ";
        }
        cout << "\n";
    }
};

struct TestCase {
    vector<int> input;
    int expectedOutput;
    int returnedOutput;
};

void printFlatten(TestCase test) {
    cout << "Input: {";
    for (auto i = test.input.begin(); i != test.input.end(); i++) {
        cout << *i;
        if (i + 1 != test.input.end()) {
            cout << ", ";
        }
    }
    cout << "}\nOutput: " << test.expectedOutput << "\n";
}

int main() {
    vector<TestCase> testCases{
        {
            .input = {1, 3, 1},
            .expectedOutput = 0,
        },
        {
            .input = {2, 1, 1, 5, 6, 2, 3, 1}, // length: 8
            .expectedOutput = 3,
        },
        {
            // Randoms drops
            .input = {1, 2, 3, 1, 4, 5, 1, 6, 1, 4, 1}, // length: 11
            .expectedOutput = 3,
        },
        {
            // Succinct drops
            .input = {1, 2, 3, 1, 1, 1, 1, 4, 5, 6, 4, 1}, // length = 12
            .expectedOutput = 4,
        },
        {
            // Repeating sequences
            .input = {1, 2, 3, 1, 2, 3, 1, 2, 3, 5, 6, 4, 1}, // length = 13
            .expectedOutput = 6,
        },
        {
            // Starting from the maximum is incorrect
            .input = {1, 2, 3, 4, 5, 4, 3, 2, 6, 1}, // length = 10
            .expectedOutput = 1,
        },
        {
            // Starting from the minimum is incorrect
            .input = {4, 5, 6, 1, 5, 4, 3}, // length = 7
            .expectedOutput = 1,
        },
        {
            // Start with highest number
            .input = {9, 8, 1, 7, 6, 5, 4, 3, 2, 1}, // length = 10
            .expectedOutput = 2,
        },
        {
            .input = {4, 5, 13, 17, 1, 7, 6, 11, 2, 8, 10, 15, 3, 9, 12, 14, 16}, // length = 17
            .expectedOutput = 10,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printFlatten(test);
        Solution solution;
        test.returnedOutput = solution.minimumMountainRemovals(test.input);
        if (test.returnedOutput == test.expectedOutput) {
            cout << "\e[32;m  => Pass\n";
        } else {
            cout << "\e[31;m  => Failed : returned " << test.returnedOutput << "\n";
            break;
        }
        cout << "\e[0;m\n";
    }

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\nElapsed = " << elapsed.count() << "ms\n";
}
