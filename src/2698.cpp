#include "common.h"

class Solution {
    pair<int, int> squares[29] = {
        {1, 1}, {9, 81}, {10, 100}, {36, 1296}, {45, 2025}, {55, 3025}, {82, 6724}, {91, 8281}, {99, 9801}, {100, 10000}, {235, 55225}, {297, 88209}, {369, 136161}, {370, 136900}, {379, 143641}, {414, 171396}, {657, 431649}, {675, 455625}, {703, 494209}, {756, 571536}, {792, 627264}, {909, 826281}, {918, 842724}, {945, 893025}, {964, 929296}, {990, 980100}, {991, 982081}, {999, 998001}, {1000, 1000000},
    };

  public:
    int punishmentNumber(int n) {
        int i = 0;
        int sum = 0;
        while (i < 29 && squares[i].first <= n) {
            sum += squares[i].second;
            i++;
        }

        return sum;
    }

    // To find squares that sum to orignal number
    // void findSquare() {
    //     cout << "{";
    //     for (int i = 1; i <= 1000; i++) {
    //         // cout << "try " << i << endl;
    //         int square = i * i;
    //         string s = to_string(square);
    //         if (find(i, s)) {
    //             cout << "{" << i << "," << (i * i) << "},";
    //             // cout << "found " << i << endl;
    //         }
    //     }
    //     cout << "}";
    // }
    // bool find(int n, string squareString) {
    //     if (squareString.length() == 0 && n == 0) {
    //         return true;
    //     }
    //     for (int i = 1; i <= squareString.length(); i++) {
    //         string subs = squareString.substr(0, i);
    //         string subs2 = squareString.substr(i);
    //         if (find(n - atoi(subs.c_str()), subs2)) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }
};

int main() {
    TestSuite<int, int> testSuite("Punishement number", "n");
    testSuite.addTestCases({
        // Original test cases
        {
            182,
            10,
        },
        {
            1478,
            37,
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::punishmentNumber, testSuite);
}
