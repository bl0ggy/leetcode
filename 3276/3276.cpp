#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    int maxScore(vector<vector<int>> &grid) {
        for (vector<int> &row : grid) {
            std::sort(row.rbegin(), row.rend());
        }

        vector<size_t> indices(grid.size(), 0);
        return getMax(grid, indices, grid[0].size());

        int sum = 0;
        for (int i = 0; i < grid.size(); i++) {
            sum += grid[i][indices[i]];
        }

        return sum;
    }

    int getMax(const vector<vector<int>> &grid, const vector<size_t> &indices, const size_t rowSize, int callCount = 0) {
        cout << "indices\n";
        print(indices);
        if (callCount > 2)
            return 0;
        vector<vector<size_t>> duplicateIndexes = getDuplicates(grid, indices);
        cout << "duplicatesIndexes\n";
        print(duplicateIndexes);
        if (duplicateIndexes.size() == 0) {
            int sum = 0;
            for (int i = 0; i < grid.size(); i++) {
                sum += grid[i][indices[i]];
            }
            return sum;
        }
        /*for(auto dups : duplicateIndexes) {
            for(auto i : dups) {
                std::cout << i << " ";
            }
            std::cout << "\n  ";
        }*/
        vector<size_t> indicesToNotIncrement(duplicateIndexes.size(), 0);
        int maxValue = 0;
        bool stop = false;
        int loopCount = 0;
        while (!stop && loopCount < 10) {
            /*for(int i = 0; i < indices.size(); i++) {
                if(indices[i] == rowSize - 1) {
                    return maxValue; // No more offset possible
                }
                currentOffset[i]++;
            }*/

            vector<size_t> newIndices = indices; // Clone
            for (int i = 0; i < indicesToNotIncrement.size(); i++) {
                // newIndices[duplicateIndexes[i][indicesToNotIncrement[i]]]++;
                for (int j = 0; j < duplicateIndexes[i].size(); j++) {
                    if (j == indicesToNotIncrement[i]) {
                        continue;
                    }
                    newIndices[duplicateIndexes[i][j]]++;
                    if (newIndices[duplicateIndexes[i][j]] == rowSize) {
                        cout << "max indice";
                        return maxValue; // No more offset possible
                    }
                }
            }
            cout << "newIndices\n";
            print(newIndices);
            maxValue = max(maxValue, getMax(grid, newIndices, rowSize, callCount + 1));

            for (int i = 0; i < indicesToNotIncrement.size(); i++)
                 {
                    if (indicesToNotIncrement[i] == duplicateIndexes[i].size() - 1) {
                        stop = true;
                    }
                }

            for (int i = 0; i < indicesToNotIncrement.size(); i++) {
                if (indicesToNotIncrement[i] != duplicateIndexes[i].size()) {
                    indicesToNotIncrement[i]++;
                    cout << "idx++ " << i << " " << indicesToNotIncrement[i] << "\n";
                    break;
                }
                indicesToNotIncrement[i] = 0;
                cout << "idx=0 " << i << "\n";
            }
            loopCount++;
        }
        return maxValue;
    }

    vector<vector<size_t>> getDuplicates(const vector<vector<int>> &grid, const vector<size_t> &indices) {
        // cout << grid.size();
        // cout << indices.size();
        vector<int> column(grid.size());
        for (int i = 0; i < grid.size(); i++) {
            column[i] = grid[i][indices[i]];
        }

        vector<vector<size_t>> duplicates;
        for (int i = 0; i < column.size(); i++) {
            vector<size_t> duplicateIndices;
            duplicateIndices.push_back(i);
            for (int j = i + 1; j < column.size(); j++) {
                if (column[j] == column[i]) {
                    duplicateIndices.push_back(j);
                }
            }

            if (duplicateIndices.size() > 1) {
                duplicates.emplace_back(duplicateIndices);
            }
        }

        return duplicates;
    }

    void print(vector<vector<int>> &grid) {
        for (vector<int> &row : grid) {
            for (int &col : row) {
                std::cout << col << " ";
            }
            std::cout << "\n";
        }
    }

    void print(vector<vector<size_t>> &grid) {
        for (vector<size_t> &row : grid) {
            for (size_t &col : row) {
                std::cout << col << " ";
            }
            std::cout << "\n";
        }
    }

    void print(const vector<size_t> &indices) {
        for (size_t i : indices) {
            cout << i << " ";
        }
        cout << "\n";
    }
};

int main() {
    vector<vector<int>> grid{{3, 3, 1}, {3, 3, 2}, {3, 3, 3}};

    auto start = chrono::system_clock::now();

    Solution solution;
    solution.maxScore(grid);

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << elapsed.count() << '\n';
}
