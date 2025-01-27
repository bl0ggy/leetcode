#include "common.h"

class Solution {
  public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries) {
        unordered_map<int, list<int>> prerequisitesMap;                                   // desired -> required[]
        vector<vector<bool>> isPrerequisite(numCourses, vector<bool>(numCourses, false)); // [required][desired] -> isPrerequisite
        for (auto v : prerequisites) {
            prerequisitesMap[v[1]].push_back(v[0]);
        }

        for (int desired = 0; desired < numCourses; desired++) {
            deque<int> queue;
            queue.push_back(desired);
            while (queue.size()) {
                int currentDesired = queue.front();
                queue.pop_front();
                for (auto required : prerequisitesMap[currentDesired]) {
                    if (!isPrerequisite[required][desired]) {
                        isPrerequisite[required][desired] = true;
                        queue.push_back(required);
                    }
                }
            }
        }

        vector<bool> ans;
        for (auto q : queries) {
            ans.push_back(isPrerequisite[q[0]][q[1]]);
        }

        return ans;
    }
};

int main() {
    TestSuite<vector<bool>, int, vector<vector<int>>, vector<vector<int>>> testSuite("Is prerequisite", "numCourse", "prerequisites", "queries");
    testSuite.addTestCases({
        // Original test cases
        {
            {false, true},
            2,
            {{1, 0}},
            {{0, 1}, {1, 0}},
        },
        {
            {false, false},
            2,
            {},
            {{1, 0}, {0, 1}},
        },
        {
            {true, true},
            3,
            {{1, 2}, {1, 0}, {2, 0}},
            {{1, 0}, {1, 2}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::checkIfPrerequisite, testSuite);
}
