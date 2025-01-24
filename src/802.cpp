#include "common.h"

class Solution {
  public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph) {
        vector<int> ans;
        int n = graph.size();
        vector<int> safe(n); // Memoization: 0=unknown, 1=true, 2=loop/false

        for (int node = 0; node < n; node++) {
            if (findTerminalNode(graph, safe, node)) {
                ans.push_back(node);
            }
        }

        return ans;
    }
    bool findTerminalNode(vector<vector<int>> &graph, vector<int> &safe, int node) {
        if (graph[node].size() == 0) {
            return true;
        }
        if (safe[node] != 0) {
            return safe[node] == 1 ? true : false;
        }
        safe[node] = 2;
        bool ans = true;
        for (int nextNodeIndex = 0; nextNodeIndex < graph[node].size(); nextNodeIndex++) {
            int nextNode = graph[node][nextNodeIndex];
            if (!findTerminalNode(graph, safe, nextNode)) {
                return false;
            }
        }

        safe[node] = 1;
        return ans;
    }
};

int main() {
    TestSuite<vector<int>, vector<vector<int>>> testSuite("Safe nodes", "graph");
    testSuite.addTestCases({
        // Original test cases
        {
            {2, 4, 5, 6},
            {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}},
        },
        {
            {4},
            {{1, 2, 3, 4}, {1, 2}, {3, 4}, {0, 4}, {}},
        },
        // Submission test cases
        // My test cases
        {
            {0, 1, 2},
            {{2}, {2}, {}},
        },
        {
            {},
            {{1}, {2}, {1}},
        },
    });

    Main main;
    main.runTests(&Solution::eventualSafeNodes, testSuite);
}
