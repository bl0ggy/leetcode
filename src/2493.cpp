#include "common.h"

class Solution {
  public:
    int magnificentSets(int n, vector<vector<int>> &edges) {
        array<int, 501> groups;
        groups.fill(-1);
        unordered_map<int, list<int>> nodesMap;

        for (auto edge : edges) {
            nodesMap[edge[0]].push_back(edge[1]);
            nodesMap[edge[1]].push_back(edge[0]);
        }

        vector<unordered_set<int>> graphs;
        array<bool, 501> visited;
        visited.fill(false);
        int currentGraph = -1;
        for (int i = 1; i <= n; i++) {
            if (visited[i]) {
                continue;
            }
            graphs.push_back({});
            currentGraph++;
            deque<int> queue;
            queue.push_back(i);
            while (queue.size()) {
                int current = queue.front();
                queue.pop_front();
                graphs[currentGraph].insert(current);

                if (visited[current]) {
                    continue;
                }
                visited[current] = true;

                for (int i : nodesMap[current]) {
                    queue.push_back(i);
                }
            }
        }

        int maxGroups = 0;
        for (auto graph : graphs) {
            int maxGroupsLocal = 0;
            for (auto graphNode : graph) {
                int nextGroup = 1;
                deque<pair<int, int>> queue;
                unordered_map<int, int> mapNodeGroup;
                queue.push_back({graphNode, nextGroup});
                mapNodeGroup[graphNode] = nextGroup;
                while (queue.size()) {
                    auto [node, group] = queue.front();
                    queue.pop_front();
                    nextGroup = group + 1;
                    for (auto nextNode : nodesMap[node]) {
                        if (mapNodeGroup.contains(nextNode)) {     // Node already visited and assigned to a group
                            if (mapNodeGroup[nextNode] == group) { // but the group is not 1 level above/below
                                return -1;
                            }
                            continue;
                        }

                        queue.push_back({nextNode, nextGroup});
                        mapNodeGroup[nextNode] = nextGroup;
                    }
                }
                maxGroupsLocal = max(maxGroupsLocal, nextGroup - 1);
            }
            maxGroups += maxGroupsLocal;
        }

        return maxGroups;
    }
};

int main() {
    TestSuite<int, int, vector<vector<int>>> testSuite("Max groups", "n", "edges");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            6,
            {{1, 2}, {1, 4}, {1, 5}, {2, 6}, {2, 3}, {4, 6}},
        },
        {
            -1,
            3,
            {{1, 2}, {2, 3}, {3, 1}},
        },
        // Submission test cases
        // My test cases
        {
            4,
            4,
            {{1, 2}, {3, 4}},
        },
        {
            6,
            7,
            {{1, 2}, {2, 3}, {3, 4}, {6, 2}, {4, 7}},
        },
        {
            -1,
            7,
            {{1, 2}, {2, 3}, {3, 4}, {6, 2}, {4, 7}, {6, 7}},
        },
        {
            5,
            6,
            {{1, 2}, {2, 3}, {3, 4}, {2, 5}, {5, 6}},
        },
    });

    Main main;
    main.runTests(&Solution::magnificentSets, testSuite);
}
