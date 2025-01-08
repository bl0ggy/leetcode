#include "common.h"

class Solution {
  public:
    // Binary search
    // Length = Len(A) + Len(B)
    // The k index to find is:
    //   If Length is odd: k = L / 2 (truncated)
    //   Otherwise       : k = L / 2 and k-1 = k - 1
    // Goal: Take half index of each list
    // A: [ [Al], Ah, [Ar] ]
    // B: [ [Bl], Bh, [Br] ]
    // If indexAh < indexBh: Al < Br
    // else                : Bl < Ar
    // Make A the list with small half value (exchange lists if needed)
    // If k > indexAhalf + indexBhalf : Discard Al
    // Else                           : Discard Br
    // Repeat until one list is empty and return the median of the other list
    double findMedianSortedArrays(vector<int> &A, vector<int> &B) {
        int la = A.size();
        int lb = B.size();
        int l = la + lb;
        if (l % 2 == 1) {
            return getMedian(A, B, l / 2, 0, la - 1, 0, lb - 1);
        } else {
            int km1 = getMedian(A, B, l / 2 - 1, 0, la - 1, 0, lb - 1);
            int k = getMedian(A, B, l / 2, 0, la - 1, 0, lb - 1);
            return (k + km1) / 2.;
        }
    }

    int getMedian(vector<int> &A, vector<int> &B, int k, int aStart, int aEnd, int bStart, int bEnd) {
        if (aEnd < aStart) {
            return B[k - aStart];
        }
        if (bEnd < bStart) {
            return A[k - bStart];
        }
        int a = (aStart + aEnd) / 2, b = (bStart + bEnd) / 2;
        if (k > a + b) {
            // Discard lower block
            if (A[a] > B[b]) {
                return getMedian(A, B, k, aStart, aEnd, b + 1, bEnd);
            } else {
                return getMedian(A, B, k, a + 1, aEnd, bStart, bEnd);
            }
        } else {
            // Discard higher block
            if (A[a] > B[b]) {
                return getMedian(A, B, k, aStart, a - 1, bStart, bEnd);
            } else {
                return getMedian(A, B, k, aStart, aEnd, bStart, b - 1);
            }
        }
    }
};

int main() {
    TestSuite<double, vector<int>, vector<int>> testSuite("median", "list 1", "list 2");
    testSuite.addTestCases({
        // Original test cases
        {
            2,
            {1, 3},
            {2},
        },
        {
            2.5,
            {1, 2},
            {3, 4},
        },
        // My test cases
        {
            8.5,
            {2, 5, 23, 26},
            {4, 8, 9, 10},
        },
        {
            9.5,
            {23, 26},
            {4, 8, 9, 10},
        },
        {
            3.5,
            {2},
            {3, 4, 5},
        },
    });

    Main main;
    return main.runTests(&Solution::findMedianSortedArrays, testSuite);
}
