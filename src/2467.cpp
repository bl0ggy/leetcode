#include "common.h"

class Solution {
    int bestPathValue = INT_MIN;

  public:
    int mostProfitablePath(vector<vector<int>> &edges, int bob, vector<int> &amount) {
        vector<vector<int>> nodeToAdjacent(edges.size() + 1);
        for (auto e : edges) {
            nodeToAdjacent[e[0]].push_back(e[1]);
            nodeToAdjacent[e[1]].push_back(e[0]);
        }
        deque<int> bobsPath;
        bobsPath.push_front(bob);
        vector<bool> visited(edges.size() + 1, false);
        visited[bob] = true;
        findBobPath(nodeToAdjacent, bobsPath, visited);

        visited = vector<bool>(edges.size() + 1, false);
        recurse(nodeToAdjacent, amount, visited, bobsPath, 0, 0);
        return bestPathValue;
    }

    bool findBobPath(vector<vector<int>> &nodeToAdjacent, deque<int> &bobsPath, vector<bool> &visited) {
        int current = bobsPath.front();
        if (current == 0) {
            return true;
        }

        for (auto n : nodeToAdjacent[bobsPath.front()]) {
            if (visited[n]) {
                continue;
            }
            bobsPath.push_front(n);
            visited[n] = true;
            if (findBobPath(nodeToAdjacent, bobsPath, visited)) {
                return true;
            }
            visited[n] = false;
            bobsPath.pop_front();
        }

        return false;
    }

    void recurse(vector<vector<int>> &nodeToAdjacent, vector<int> &amount, vector<bool> &visited, deque<int> &bobsPath, int posAlice, int sumAlice) {
        int posBob = bobsPath.size() > 0 ? bobsPath.back() : -1;
        int nextSumAlice = sumAlice;
        if (posBob == posAlice) {
            nextSumAlice += amount[posAlice] / 2;
        } else {
            nextSumAlice += amount[posAlice];
        }

        if (posAlice != 0 && nodeToAdjacent[posAlice].size() == 1) {
            bestPathValue = max(bestPathValue, nextSumAlice);
            return;
        }

        int amountPosBob = 0;
        if (posBob >= 0) {
            bobsPath.pop_back();
            amountPosBob = amount[posBob];
            amount[posBob] = 0;
        }
        visited[posAlice] = true;

        for (auto adjacent : nodeToAdjacent[posAlice]) {
            if (visited[adjacent]) {
                continue;
            }

            recurse(nodeToAdjacent, amount, visited, bobsPath, adjacent, nextSumAlice);
        }

        if (posBob >= 0) {
            amount[posBob] = amountPosBob;
            bobsPath.push_back(posBob);
        }
        visited[posAlice] = false;
    }
};

int main() {
    TestSuite<int, vector<vector<int>>, int, vector<int>> testSuite("Alice's cost", "edges", "bob", "amount");
    testSuite.addTestCases({
        // Original test cases
        {
            6,
            {{0, 1}, {1, 2}, {1, 3}, {3, 4}},
            3,
            {-2, 4, 2, -4, 6},
        },
        {
            -7280,
            {{0, 1}},
            1,
            {-7280, 2350},
        },
        // Submission test cases
        {
            15584,
            {{0, 21}, {0, 6}, {0, 29}, {1, 3}, {1, 38}, {2, 32}, {2, 34}, {2, 27}, {3, 24}, {3, 8}, {4, 5}, {4, 21}, {5, 11}, {5, 28}, {6, 27}, {7, 23}, {7, 21}, {8, 12}, {8, 22}, {8, 36}, {9, 10}, {10, 17}, {12, 15}, {13, 24}, {14, 29}, {16, 25}, {16, 35}, {16, 39}, {17, 19}, {17, 39}, {18, 37}, {18, 26}, {20, 27}, {26, 38}, {26, 30}, {29, 30}, {29, 39}, {30, 31}, {33, 34}},
            31,
            {562, 5200, 8954, -1176, 3208, -140, 940, 9548, -662, -4974, -9054, -5868, -3888, 404, -5184, 418, 3890, -9434, -8184, 642, -5484, -4542, -372, -7818, -268, 4512, -2648, -9016, 8782, 542, -8812, -7262, -9804, 6622, -7030, 8164, 8354, -8176, 5412, -5648},
        },
        // My test cases
        {
            7,
            {{0, 4}, {4, 3}, {3, 2}, {2, 1}},
            3,
            {-2, 4, 2, -4, 6},
        },
        {
            1,
            {{0, 1}, {1, 2}},
            2,
            {0, 2, 4},
        },
    });

    Main main;
    main.runTests(&Solution::mostProfitablePath, testSuite);
}
