#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    int longestSquareStreak(vector<vector<int>> &grid) {
        size_t rows = grid.size();
        size_t cols = grid[0].size();
        vector<bool> dpRow(rows, 1);

        size_t c;
        for (c = 1; c < cols; c++) {
            bool foundOne = false;
            auto tmpDpRow = dpRow;
            for (size_t r = 0; r < rows; r++) {
                bool ans = (dpRow[r] && grid[r][c - 1] < grid[r][c]);
                if (r > 0) {
                    ans |= dpRow[r - 1] && (grid[r - 1][c - 1] < grid[r][c]);
                }
                if (r + 1 < rows) {
                    ans |= dpRow[r + 1] && grid[r + 1][c - 1] < grid[r][c];
                }

                tmpDpRow[r] = ans;
                foundOne |= ans;
            }
            if (!foundOne) {
                return c - 1;
            }
            dpRow = tmpDpRow;
        }

        return c - 1;
    }

    void print(vector<bool> vec) {
        for (bool val : vec) {
            cout << val << " ";
        }
        cout << "\n";
    }
};

struct TestCase {
    vector<vector<int>> input;
    int expectedOutput;
    int returnedOutput;
};

void printFlatten(TestCase test) {
    cout << "Input: {";
    for (auto row = test.input.begin(); row != test.input.end(); row++) {
        cout << "{";
        for (auto col = row->begin(); col < row->end(); col++) {
            cout << *col;
            if (col + 1 != row->end()) {
                cout << ", ";
            }
        }
        cout << "}";
        if (row + 1 != test.input.end()) {
            cout << ",\n";
        }
    }
    cout << "}\nOutput: " << test.expectedOutput << "\n";
}

int main() {
    vector<TestCase> testCases{
        {
            .input = {{2, 4, 3, 5}, {5, 4, 9, 3}, {3, 4, 2, 11}, {10, 9, 13, 15}},
            .expectedOutput = 3,
        },
        {
            .input = {{3, 2, 4}, {2, 1, 9}, {1, 1, 7}},
            .expectedOutput = 0,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printFlatten(test);
        Solution solution;
        test.returnedOutput = solution.longestSquareStreak(test.input);
        if (test.returnedOutput == test.expectedOutput) {
            cout << "\e[32;m  => Pass\n";
        } else {
            cout << "\e[31;m  => Failed : returned " << test.returnedOutput << "\n";
        }
        cout << "\e[0;m\n";
    }

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\nElapsed = " << elapsed.count() << "ms\n";
}
