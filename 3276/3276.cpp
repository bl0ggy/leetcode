#include <cassert>
#include <chrono>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    int maxScore(vector<vector<int>> &grid) {
        const size_t rows = grid.size();
        const size_t cols = grid[0].size();
        const size_t cells = rows * cols;
        vector<pair<int, int>> valueRows(cells);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                valueRows[i * cols + j] = {grid[i][j], i};
            }
        }
        sort(valueRows.begin(), valueRows.end());

        const int maskMax = 1 << rows;
        vector<int> dp(maskMax);
        dp[0] = 0;
        size_t l = 0, r = 0;
        while (l < cells) {
            while (r < cells && valueRows[l].first == valueRows[r].first) {
                r++;
            }
            vector<int> newDp = dp;
            for (size_t mask = 0; mask < maskMax; mask++) {
                for (size_t i = l; i < r; i++) {
                    auto [value, row] = valueRows[i];
                    if (mask & (1 << row)) {
                        continue;
                    }
                    newDp[mask | (1 << row)] = max(newDp[mask | (1 << row)], dp[mask] + value);
                }
            }
            dp = newDp;
            l = r;
        }

        return *max_element(dp.begin(), dp.end());
    }

    // int maxScore(vector<vector<int>> &grid) {
    //     for (vector<int> &row : grid) {
    //         std::sort(row.rbegin(), row.rend());
    //     }
    //     // print(grid);
    //     // return 0;
    //     rows = grid.size();
    //     cols = grid[0].size();
    //     vector<size_t> selectedColumns(rows, 0);
    //
    //     solve(grid, selectedColumns);
    //     // bool limitReached = false;
    //     // while (!limitReached) {
    //     //     // cout << "selectedColumns :";
    //     //     // print(selectedColumns);
    //     //     auto [sum, hasDuplicates] = getSum(grid, selectedColumns);
    //     //     if (hasDuplicates) {
    //     //         maxWithDuplicates = max(maxWithDuplicates, sum);
    //     //         // cout << "maxWithDups " << maxWithDuplicates << endl;
    //     //     } else {
    //     //         maxWithoutDuplicates = max(maxWithoutDuplicates, sum);
    //     //         // cout << "maxWithoutDups " << maxWithoutDuplicates << endl;
    //     //     }
    //     //
    //     //     if (hasDuplicates) {
    //     //     }
    //     //
    //     //     for (int i = 0; i < rows; i++) {
    //     //         if (selectedColumns[i] != cols - 1) {
    //     //             selectedColumns[i]++;
    //     //             break;
    //     //         } else if (i == rows - 1) {
    //     //             limitReached = true;
    //     //         }
    //     //         selectedColumns[i] = 0;
    //     //     }
    //     // }
    //
    //     if (maxWithoutDuplicates == -1) {
    //         return maxWithDuplicates;
    //     }
    //     return maxWithoutDuplicates;
    // }
    //
    // void solve(vector<vector<int>> &grid, vector<size_t> &selectedColumns) {
    //     // cout << "selected:";
    //     // print(selectedColumns);
    //     auto [sum, hasDuplicates] = getSum(grid, selectedColumns);
    //     if (!hasDuplicates) {
    //         maxWithoutDuplicates = max(maxWithoutDuplicates, sum);
    //         return;
    //     } else {
    //         maxWithDuplicates = max(maxWithDuplicates, sum);
    //     }
    //
    //     auto duplicates = getDuplicates(grid, selectedColumns);
    //     for (auto duplicate : duplicates) {
    //         for (int i = 0; i < duplicate.size(); i++) {
    //             vector<size_t> newSelectedColumns = selectedColumns;
    //             bool cancel = false;
    //             for (int j = 0; j < duplicate.size(); j++) {
    //                 if (i == j) {
    //                     continue;
    //                 }
    //                 newSelectedColumns[j]++;
    //                 if (newSelectedColumns[j] >= cols) {
    //                     cancel = true;
    //                 }
    //             }
    //             if (!cancel) {
    //                 // print(selectedColumns);
    //                 // print(newSelectedColumns);
    //                 // exit(1);
    //                 solve(grid, newSelectedColumns);
    //             }
    //         }
    //     }
    // }
    //
    // vector<vector<int>> getDuplicates(const vector<vector<int>> &grid, const vector<size_t> &selectedColumns) {
    //     // // cout << grid.size();
    //     // // cout << indices.size();
    //     // vector<int> column(grid.size());
    //     // for (int i = 0; i < grid.size(); i++) {
    //     //     column[i] = grid[i][selectedColumns[i]];
    //     // }
    //     //
    //     // vector<vector<size_t>> duplicates;
    //     // for (int i = 0; i < column.size(); i++) {
    //     //     vector<size_t> duplicateIndices;
    //     //     duplicateIndices.push_back(i);
    //     //     for (int j = i + 1; j < column.size(); j++) {
    //     //         if (column[j] == column[i]) {
    //     //             duplicateIndices.push_back(j);
    //     //         }
    //     //     }
    //     //
    //     //     if (duplicateIndices.size() > 1) {
    //     //         duplicates.emplace_back(duplicateIndices);
    //     //     }
    //     // }
    //     //
    //     // return duplicates;
    //     unordered_map<int, vector<int>> values;
    //     for (int i = 0; i < grid.size(); i++) {
    //         if (values.count(grid[i][selectedColumns[i]]) == 0) {
    //             values[grid[i][selectedColumns[i]]] = {i};
    //         } else {
    //             values[grid[i][selectedColumns[i]]].push_back(i);
    //         }
    //     }
    //     vector<vector<int>> out;
    //     for (auto it = values.begin(); it != values.end(); it++) {
    //         if (it->second.size() <= 1) {
    //             continue;
    //         }
    //         out.push_back(it->second);
    //     }
    //     return out;
    // }
    //
    // pair<int, bool> getSum(const vector<vector<int>> &grid, const vector<size_t> &selectedColumns) {
    //     int sum = 0;
    //     bool hasDuplicates = false;
    //     set<int> usedValues;
    //     for (int i = 0; i < grid.size(); i++) {
    //         if (usedValues.count(grid[i][selectedColumns[i]]) == 0) {
    //             usedValues.insert(grid[i][selectedColumns[i]]);
    //         } else {
    //             hasDuplicates = true;
    //             continue;
    //         }
    //         sum += grid[i][selectedColumns[i]];
    //     }
    //     return {sum, hasDuplicates};
    // }
    //
    // void print(const vector<vector<int>> &grid) {
    //     for (const vector<int> &row : grid) {
    //         for (const int &col : row) {
    //             std::cout << col << " ";
    //         }
    //         std::cout << "\n";
    //     }
    // }
    //
    // void print(const unordered_map<int, vector<size_t>> &grid) {
    //     for (const pair<const int, vector<size_t>> &row : grid) {
    //         for (const size_t &col : row.second) {
    //             std::cout << row.first << "|" << col << " ";
    //         }
    //         std::cout << "\n";
    //     }
    // }
    //
    // void print(const vector<size_t> &indices) {
    //     // cout << "aaaa" << endl;
    //     // cout << "indices size " << indices.size() << endl;
    //     for (size_t i : indices) {
    //         // cout << "b" << endl;
    //         cout << i << " ";
    //     }
    //     cout << "\n";
    // }
};

int main() {
    // vector<vector<int>> grid{{1, 2}, {1, 3}};
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
