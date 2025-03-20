#include "common.h"

class Solution {
  public:
    vector<int> minimumCost(int n, vector<vector<int>> &edges, vector<vector<int>> &query) {
        // Create groups of vertices
        // Calculate the & of all weights in the group
        // Create pairs of list,cost with list containing all edges of tha group
        // For every query, check if both numbers are in a list, if yes return the cost, otherwise return -1

        int sizeEdges = edges.size(), sizeQuery = query.size();
        vector<vector<pair<int, int>>> connectedVertices(n); // vertice:vertice,weight
        for (int i = 0; i < sizeEdges; i++) {
            connectedVertices[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            connectedVertices[edges[i][1]].push_back({edges[i][0], edges[i][2]});
        }

        vector<int> vertexToGroup(n, -1);
        vector<int> groupToCost;
        int currentGroup = 0;
        for (int cvIndex = 0; cvIndex < n; cvIndex++) {
            if (connectedVertices[cvIndex].size() == 0) {
                continue;
            }
            auto vertexStart = connectedVertices[cvIndex][0];
            if (vertexToGroup[vertexStart.first] != -1) {
                continue;
            }
            deque<int> q;
            int cost = vertexStart.second;
            q.push_back(vertexStart.first);
            while (!q.empty()) {
                auto currentVertex = q.back();
                q.pop_back();
                vertexToGroup[currentVertex] = currentGroup;
                for (auto nextVertex : connectedVertices[currentVertex]) {
                    cost &= nextVertex.second; // Count the cost even if we already passed this vertex
                    if (vertexToGroup[nextVertex.first] != -1) {
                        continue;
                    }
                    q.push_back(nextVertex.first);
                }
            }
            groupToCost.push_back(cost);
            currentGroup++;
        }

        vector<int> ans(sizeQuery, -1);
        for (int i = 0; i < sizeQuery; i++) {
            int a = query[i][0];
            int b = query[i][1];
            if (vertexToGroup[a] == vertexToGroup[b] && vertexToGroup[a] != -1) {
                ans[i] = groupToCost[vertexToGroup[a]];
            }
        }

        return ans;
    }
};

int main() {
    TestSuite<vector<int>, int, vector<vector<int>>, vector<vector<int>>> testSuite("Minimum cost", "n", "edges", "query");
    testSuite.addTestCases({
        // Original test cases
        {
            {1, -1},
            5,
            {{0, 1, 7}, {1, 3, 7}, {1, 2, 1}},
            {{0, 3}, {3, 4}},
        },
        {
            {0},
            3,
            {{0, 2, 7}, {0, 1, 15}, {1, 2, 6}, {1, 2, 1}},
            {{1, 2}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::minimumCost, testSuite);
}
