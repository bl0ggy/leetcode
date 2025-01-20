#include "common.h"

class Solution {
  public:
    int firstCompleteIndex(vector<int> &arr, vector<vector<int>> &mat) {
        array<pair<int, int>, 100001> map; // 1-indexed
        int a = arr.size();                // arr size
        int n = mat.size();                // Number or rows
        int m = mat[0].size();             // Number of columns
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                map[mat[row][col]] = {row, col};
            }
        }

        vector<int> rowCount(n);
        vector<int> colCount(m);
        int answer = -1;
        for (int i = 0; i < a; i++) {
            auto [row, col] = map[arr[i]];
            rowCount[row]++;
            colCount[col]++;

            if (rowCount[row] == m || colCount[col] == n) { // n and m are reversed, a row is full when all columns are found and vice versa
                answer = i;
                break;
            }
        }

        return answer;
    }
};

int main() {
    TestSuite<int, vector<int>, vector<vector<int>>> testSuite("First index", "arr", "mat");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {1, 3, 4, 2},
            {{1, 4}, {2, 3}},
        },
        {
            3,
            {2, 8, 7, 4, 1, 3, 5, 6, 9},
            {{3, 2, 5}, {1, 4, 6}, {8, 7, 9}},
        },
        // Submission test cases
        {
            1,
            {1, 4, 5, 2, 6, 3},
            {{4, 3, 5}, {1, 2, 6}},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::firstCompleteIndex, testSuite);
}
