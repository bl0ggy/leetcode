#include "common.h"

class Solution {
  public:
    int tupleSameProduct(vector<int> &nums) {
        int size = nums.size();
        unordered_map<int, int> products;

        // Compute only half of the grid as it is symmetrical
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                products[nums[i] * nums[j]]++;
            }
        }

        int total = 0;
        for (auto p : products) {
            if (p.second >= 2) {
                // Formula for sum of consecutive integers: (n / 2) * (first + last),
                // then *8 because there are 8 arrangements for each pair
                total += ((p.second) * (p.second - 1) / 2) * 8;
            }
        }

        return total;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Tuples with same product", "nums");
    testSuite.addTestCases({
        // Original test cases
        {
            8,
            {2, 3, 4, 6},
        },
        {
            16,
            {1, 2, 4, 5, 10},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::tupleSameProduct, testSuite);
}
