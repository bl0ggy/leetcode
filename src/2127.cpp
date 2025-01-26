#include "common.h"

class Solution {
  public:
    int maximumInvitations(vector<int> &favorite) {
        const int size = favorite.size();
        if (size < 4) {
            return size;
        }

        int longestCycle = 0, longestChain = 0;
        unordered_map<int, list<int>> reversedFavorite;
        vector<pair<int, int>> size2cycles;
        vector<bool> visited(size, false);

        for (int i = 0; i < size; i++) {
            reversedFavorite[favorite[i]].push_back(i);
        }

        for (int i = 0; i < size; i++) {
            if (visited[i]) {
                continue;
            }
            unordered_map<int, int> chain;
            int current = i, previous = i, length = 1;
            while (!visited[current]) {
                visited[current] = true;
                chain[current] = length++;
                previous = current;
                current = favorite[current];
            }

            if (chain.count(current)) {
                int length = chain[previous] - chain[current] + 1;
                longestCycle = max(longestCycle, length);
                if (length == 2) {
                    size2cycles.push_back({previous, current});
                }
            }
        }

        for (auto [a, b] : size2cycles) {
            longestChain += countChain(a, b, reversedFavorite) + countChain(b, a, reversedFavorite) + 2;
        }

        return max(longestCycle, longestChain);
    }

    int countChain(int a, int b, unordered_map<int, list<int>> &reversedFavorite) {
        int m = 0;
        for (auto i : reversedFavorite[a]) {
            if (i == b) {
                continue;
            }

            m = max(m, 1 + countChain(i, a, reversedFavorite));
        }

        return m;
    }
};

int main() {
    TestSuite<int, vector<int>> testSuite("Max employees", "favorite");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            {2, 2, 1, 2},
        },
        {
            3,
            {1, 2, 0},
        },
        {
            4,
            {3, 0, 1, 4, 1},
        },
        // Submission test cases
        {
            11,
            {1, 0, 3, 2, 5, 6, 7, 4, 9, 8, 11, 10, 11, 12, 10},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::maximumInvitations, testSuite);
}
