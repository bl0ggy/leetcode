#include "common.h"

class Solution {
  public:
    int countCompleteComponents(int n, vector<vector<int>> &edges) {
        int ans = 0;

        vector<vector<int>> edgesMap(n);
        for (auto &edge : edges) {
            edgesMap[edge[0]].push_back(edge[1]);
            edgesMap[edge[1]].push_back(edge[0]);
        }

        int currentGroup = 0;
        vector<unordered_set<int>> groups; // group:edge,connections
        vector<int> visited(n);
        for (int startEdge = 0; startEdge < edgesMap.size(); startEdge++) {
            if (visited[startEdge]) {
                continue;
            }
            groups.push_back({});

            // Find all edges of the group
            deque<int> q;
            q.push_front(startEdge);
            while (!q.empty()) {
                int edge = q.front();
                q.pop_front();
                visited[edge] = true;

                groups[currentGroup].insert(edge);

                for (auto &adjacent : edgesMap[edge]) {
                    if (visited[adjacent]) {
                        continue;
                    }

                    q.push_back(adjacent);
                }
            }

            // Check if the group is complete
            bool complete = true;
            int edgesInGroup = groups[currentGroup].size();
            for (auto &edge : groups[currentGroup]) {
                if (edgesMap[edge].size() != edgesInGroup - 1) {
                    complete = false;
                    break;
                }
            }

            if (complete) {
                ans++;
            }
            currentGroup++;
        }

        return ans;
    }
};

int main() {
    TestSuite<int, int, vector<vector<int>>> testSuite("Complete subgraphs", "n", "edges");
    testSuite.addTestCases({
        // Original test cases
        {
            3,
            6,
            {{0, 1}, {0, 2}, {1, 2}, {3, 4}},
        },
        {
            1,
            6,
            {{0, 1}, {0, 2}, {1, 2}, {3, 4}, {3, 5}},
        },
        // Submission test cases
        // My test cases
        {
            1,
            4,
            {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {1, 3}, {2, 0}},
        },
        {
            0,
            5,
            {{0, 1}, {0, 2}, {1, 2}, {2, 3}, {2, 4}, {3, 4}},
        },
    });

    Main main;
    main.runTests(&Solution::countCompleteComponents, testSuite);
}
