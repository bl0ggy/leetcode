#include "common.h"

class Solution {
  public:
    int countPaths(int n, vector<vector<int>> &roads) {
        vector<vector<pair<int, int>>> edgeToEdges(n);
        for (int i = 0; i < roads.size(); i++) {
            edgeToEdges[roads[i][0]].push_back({roads[i][1], roads[i][2]});
            edgeToEdges[roads[i][1]].push_back({roads[i][0], roads[i][2]});
        }

        vector<long long> weights(n, LONG_LONG_MAX);
        weights[0] = 0;
        vector<long long> counts(n, 0);
        counts[0] = 1;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> heap; // weight,node
        heap.push({0, 0});

        while (!heap.empty()) {
            auto [currentWeight, currentNode] = heap.top();
            heap.pop();
            if (currentWeight > weights[currentNode]) {
                continue;
            }
            for (auto [neighbourNode, neighbourWeight] : edgeToEdges[currentNode]) {
                long long nextWeight = currentWeight + neighbourWeight;
                if (nextWeight < weights[neighbourNode]) {
                    weights[neighbourNode] = nextWeight;
                    counts[neighbourNode] = counts[currentNode];
                    heap.push({nextWeight, neighbourNode});
                } else if (nextWeight == weights[neighbourNode]) {
                    counts[neighbourNode] = (counts[neighbourNode] + counts[currentNode]) % 1000000007;
                }
            }
        }

        return counts[n - 1];
    }
    // Sounded promising but time limit exceeded at half of the text cases
    // int countPaths(int n, vector<vector<int>> &roads) {
    //     vector<vector<pair<int, int>>> edgeToEdges(n);
    //     for (int i = 0; i < roads.size(); i++) {
    //         edgeToEdges[roads[i][0]].push_back({roads[i][1], roads[i][2]});
    //         edgeToEdges[roads[i][1]].push_back({roads[i][0], roads[i][2]});
    //     }
    //
    //     long minDistance = LONG_MAX;
    //     vector<long> distances(n, LONG_MAX);
    //     unordered_map<int, int> distancesCount;
    //     deque<pair<int, long>> q;
    //     q.push_back({0, 0});
    //     while (!q.empty()) {
    //         auto [edge, totalDistance] = q.front();
    //         q.pop_front();
    //         distances[edge] = min(distances[edge], totalDistance);
    //
    //         if (edge == n - 1) {
    //             minDistance = min(minDistance, totalDistance);
    //             if (totalDistance == minDistance) {
    //                 distancesCount[totalDistance] = (distancesCount[totalDistance] + 1) % 1000000007;
    //             }
    //             continue;
    //         }
    //
    //         for (auto [nextEdge, distance] : edgeToEdges[edge]) {
    //             int nextDistance = totalDistance + distance;
    //             if (nextDistance > minDistance || nextDistance > distances[nextEdge]) {
    //                 continue;
    //             }
    //
    //             q.push_back({nextEdge, nextDistance});
    //         }
    //     }
    //
    //     return distancesCount[minDistance];
    // }
};

int main() {
    TestSuite<int, int, vector<vector<int>>> testSuite("Number of ways", "n", "roads");
    testSuite.addTestCases({
        // Original test cases
        {
            4,
            7,
            {{0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}},
        },
        {
            1,
            2,
            {{1, 0, 10}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::countPaths, testSuite);
}
