#include "common.h"

class Solution {
  public:
    // vector<int> findRedundantConnection(vector<vector<int>> &edges) {
    //     array<bool, 1001> visited{false};
    //     unordered_map<int, list<int>> adjacents;
    //     for (auto e : edges) {
    //         adjacents[e[0]].push_back(e[1]);
    //         adjacents[e[1]].push_back(e[0]);
    //     }
    //
    //     vector<vector<int>> loopEdges;
    //
    //     function<bool(deque<int> &)> dfs = [&](deque<int> &queue) -> bool {
    //         int edge = queue.back();
    //         list<int> &l = adjacents[edge];
    //
    //         if (visited[edge]) {
    //             for (int i = queue.size() - 1; i > 0 && queue[i - 1] != edge; i--) {
    //                 loopEdges.push_back({queue[i - 1], queue[i]});
    //             }
    //             return true;
    //         }
    //
    //         visited[edge] = true;
    //
    //         for (auto e : l) {
    //             if (queue.size() > 1 && e == queue[queue.size() - 2]) {
    //                 continue;
    //             }
    //             queue.push_back(e);
    //             if (dfs(queue)) {
    //                 return true;
    //             }
    //             queue.pop_back();
    //         }
    //         return false;
    //     };
    //     for (auto adjacent : adjacents) {
    //         deque<int> queue;
    //         queue.push_front(adjacent.first);
    //         if (dfs(queue)) {
    //             break;
    //         }
    //     }
    //     int m = 0;
    //     for (auto edge : loopEdges) {
    //         m = max(m, (int)(find_if(edges.begin(), edges.end(), [&](vector<int> &e) { return (e[0] == edge[0] && e[1] == edge[1]) || (e[0] == edge[1] && e[1] == edge[0]); }) - edges.begin()));
    //     }
    //     return edges[m];
    // }

    vector<int> findRedundantConnection(vector<vector<int>> &edges) {
        array<int, 1001> parents;
        for (int i = 1; i < 1001; i++) {
            parents[i] = i;
        }
        vector<int> edge;
        for (auto e : edges) {
            int node1 = e[0];
            int node2 = e[1];

            while (node1 != parents[node1]) {
                node1 = parents[node1];
            }
            while (node2 != parents[node2]) {
                node2 = parents[node2];
            }

            if (node1 == node2) {
                edge = e;
            } else {
                parents[node1] = node2;
            }
        }

        return edge;
    }
};

int main() {
    TestSuite<vector<int>, vector<vector<int>>> testSuite("Removed edge", "edges");
    testSuite.addTestCases({
        // Original test cases
        {
            {2, 3},
            {{1, 2}, {1, 3}, {2, 3}},
        },
        {
            {1, 4},
            {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}},
        },
        // Submission test cases
        {
            {2, 5},
            {{3, 4}, {1, 2}, {2, 4}, {3, 5}, {2, 5}},
        },
        // My test cases
    });

    Main main;
    main.runTests(&Solution::findRedundantConnection, testSuite);
}
