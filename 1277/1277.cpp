#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    int countSquares(vector<vector<int>> &matrix) {
        int matrixRows = matrix.size();
        int matrixCols = matrix[0].size();
        int kernelMaxSize = min(matrixRows, matrixCols);
        int count = 0;

        for (int kernelSize = 1; kernelSize <= kernelMaxSize; kernelSize++) {
            for (int mRowStart = 0; mRowStart < matrixRows - kernelSize + 1; mRowStart++) {
                for (int mColStart = 0; mColStart < matrixCols - kernelSize + 1; mColStart++) {
                    // cout << "rowStart=" << mRowStart << " colStart" << mColStart << "\n";
                    bool allOnes = true;
                    for (int mRow = mRowStart; allOnes && mRow < kernelSize + mRowStart; mRow++) {
                        for (int mCol = mColStart; allOnes && mCol < kernelSize + mColStart; mCol++) {
                            // cout << "mRow=" << mRow << " mCol=" << mCol << " " << matrix[mRow][mCol] << "\n";
                            if (matrix[mRow][mCol] == 0) {
                                allOnes = false;
                            }
                        }
                    }
                    if (allOnes) {
                        count++;
                    }
                    // cout << "(" << mRowStart << "," << mColStart << ") k=" << kernelSize << " 1s=" << allOnes << " count=" << count << "\n";
                }
            }
        }
        return count;
    }
};

int main() {
    vector<vector<int>> input{{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};
    int expectedCount = 15;

    auto start = chrono::system_clock::now();

    Solution solution;
    int count = solution.countSquares(input);

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "elapsed = " << elapsed.count() << "ms\n";
    cout << "count=" << count << "\n";
    assert(count == expectedCount);
}
