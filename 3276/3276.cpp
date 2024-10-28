#include <cassert>
#include <chrono>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

class Solution {
    int maxWithDuplicates = -1;
    int maxWithoutDuplicates = -1;

  public:
    int maxScore(vector<vector<int>> &grid) {
        for (vector<int> &row : grid) {
            std::sort(row.rbegin(), row.rend());
        }

        const size_t rows = grid.size();
        const size_t cols = grid[0].size();
        vector<size_t> indices(grid.size(), 0);
        vector<size_t> selectedColumns(rows, 0);
        bool limitReached = false;
        while (!limitReached) {
            // cout << "selectedColumns :";
            // print(selectedColumns);
            auto [sum, hasDuplicates] = getSum(grid, selectedColumns);
            if (hasDuplicates) {
                maxWithDuplicates = max(maxWithDuplicates, sum);
                // cout << "maxWithDups " << maxWithDuplicates << endl;
            } else {
                maxWithoutDuplicates = max(maxWithoutDuplicates, sum);
                // cout << "maxWithoutDups " << maxWithoutDuplicates << endl;
            }

            // for (int i = 0; i < rows; i++) {
            //     auto it = duplicateIndices.begin();
            //     std::advance(it, i);
            //     if (indicesToNotIncrement[i] == it->second.size() - 1) {
            //         stop = true;
            //     }
            // }
            for (int i = 0; i < rows; i++) {
                if (selectedColumns[i] != cols - 1) {
                    selectedColumns[i]++;
                    break;
                } else if (i == rows - 1) {
                    limitReached = true;
                }
                selectedColumns[i] = 0;
            }
        }

        if (maxWithoutDuplicates == -1) {
            return maxWithDuplicates;
        }
        return maxWithoutDuplicates;
    }

    pair<int, bool> getSum(const vector<vector<int>> &grid, const vector<size_t> &selectedColumns) {
        int sum = 0;
        bool hasDuplicates = false;
        set<int> usedValues;
        for (int i = 0; i < grid.size(); i++) {
            if (usedValues.count(grid[i][selectedColumns[i]]) == 0) {
                usedValues.insert(grid[i][selectedColumns[i]]);
            } else {
                hasDuplicates = true;
                continue;
            }
            sum += grid[i][selectedColumns[i]];
        }
        return {sum, hasDuplicates};
    }

    void print(const vector<vector<int>> &grid) {
        for (const vector<int> &row : grid) {
            for (const int &col : row) {
                std::cout << col << " ";
            }
            std::cout << "\n";
        }
    }

    void print(const unordered_map<int, vector<size_t>> &grid) {
        for (const pair<const int, vector<size_t>> &row : grid) {
            for (const size_t &col : row.second) {
                std::cout << row.first << "|" << col << " ";
            }
            std::cout << "\n";
        }
    }

    void print(const vector<size_t> &indices) {
        // cout << "aaaa" << endl;
        // cout << "indices size " << indices.size() << endl;
        for (size_t i : indices) {
            // cout << "b" << endl;
            cout << i << " ";
        }
        cout << "\n";
    }
};

int main() {
    // vector<vector<int>> grid{{3, 3, 1}, {3, 3, 2}, {3, 3, 3}};
    // vector<vector<int>> grid{{5}, {7}, {19}, {5}};
    // vector<vector<int>> grid{{1, 2, 3}, {4, 3, 2}, {1, 1, 1}};
    // vector<vector<int>> grid{{13, 14, 14}, {14, 18, 18}, {20, 14, 20}, {20, 4, 14}};
    vector<vector<int>> grid{{25, 56, 56, 56, 78}, {60, 58, 56, 56, 91}, {56, 60, 46, 15, 41}, {46, 60, 77, 20, 31}, {76, 46, 24, 78, 23}, {58, 92, 17, 60, 46}, {15, 60, 20, 25, 56}, {25, 78, 15, 90, 25}, {90, 15, 25, 10, 33}};

    auto start = chrono::system_clock::now();

    Solution solution;
    int max = solution.maxScore(grid);

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "max=" << max << "\n";
    cout << "elapsed = " << elapsed.count() << "ms\n";
}
