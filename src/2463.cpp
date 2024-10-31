#include <cassert>
#include <chrono>
#include <climits>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    long long minimumTotalDistance(vector<int> &robots, vector<vector<int>> &factories) {
        sort(robots.begin(), robots.end());
        sort(factories.begin(), factories.end());
        vector<int> flattenedFactories;
        for (auto f : factories) {
            for (int i = 0; i < f[1]; i++) {
                flattenedFactories.push_back(f[0]);
            }
        }

        size_t robotsSize = robots.size();
        size_t factoriesSize = flattenedFactories.size();
        vector<vector<long long>> distances(robotsSize + 1, vector<long long>(factoriesSize + 1, 0));
        for (int i = 0; i < robotsSize; i++) {
            distances[i][factoriesSize] = 1e12;
        }
        for (size_t r = robotsSize - 1; r < INT_MAX; r--) {
            for (size_t f = factoriesSize - 1; f < INT_MAX; f--) {
                long long a = distances[r][f + 1];
                long long b = distances[r + 1][f + 1] + abs(robots[r] - flattenedFactories[f]);
                distances[r][f] = min(a, b);
            }
        }

        return distances[0][0];
    }

    static void print(vector<int> vec) {
        cout << "{";
        for (auto it = vec.begin(); it != vec.end(); it++) {
            cout << *it;
            if (it + 1 != vec.end()) {
                cout << ", ";
            }
        }
        cout << "}";
    }

    static void print(vector<vector<int>> vec) {
        cout << "{";
        for (auto it = vec.begin(); it != vec.end(); it++) {
            cout << "{";
            for (auto it2 = it->begin(); it2 != it->end(); it2++) {
                cout << *it2;
                if (it2 + 1 != it->end()) {
                    cout << ", ";
                }
            }
            cout << "}";
            if (it + 1 != vec.end()) {
                cout << ", ";
            }
        }
        cout << "}";
    }
};

struct TestCase {
    vector<int> robots;
    vector<vector<int>> factories;
    int expectedOutput;
    int returnedOutput;
};

void printTest(TestCase test) {
    cout << "Robots: ";
    Solution::print(test.robots);
    cout << "\nFactories: ";
    Solution::print(test.factories);
    cout << "\nOutput: " << test.expectedOutput << endl;
}

//                       |               // average
//  ----- r--r- -r-r- rr-r- r--r- -rrr- // 12 robots
//  ---4- -1-1- -3--- -111- ---1- ----- // 13 factories
//               |
//  groups into blocks:
//  1:
//  ----- r
//  ---1- -
//  2:
//  ----- ---r
//  ---1
int main() {
    vector<TestCase> testCases{
        {
            .robots = {0, 4, 6},
            .factories = {{2, 2}, {6, 2}},
            .expectedOutput = 4,
        },
        {
            .robots = {1, -1},
            .factories = {{-2, 2}, {2, 1}},
            .expectedOutput = 2,
        },
        {
            // r--r------ //
            // -------f-f //
            .robots = {1, 4},
            .factories = {{8, 1}, {10, 1}},
            .expectedOutput = 13,
        },
        {
            // -------r-r //
            // f--f------ //
            .robots = {8, 10},
            .factories = {{1, 1}, {4, 1}},
            .expectedOutput = 13,
        },
        {
            // r------r-- //
            // ---f-----f //
            .robots = {1, 8},
            .factories = {{4, 1}, {10, 1}},
            .expectedOutput = 5,
        },
        {
            // ---r-----r //
            // f------f-- //
            .robots = {4, 10},
            .factories = {{1, 1}, {8, 1}},
            .expectedOutput = 5,
        },
        {
            // r--------r //
            // ---f---f-- //
            .robots = {1, 10},
            .factories = {{4, 1}, {8, 1}},
            .expectedOutput = 5,
        },
        {
            // ---r---r-- //
            // f--------f //
            .robots = {4, 8},
            .factories = {{1, 1}, {10, 1}},
            .expectedOutput = 5,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printTest(test);
        Solution solution;
        test.returnedOutput = solution.minimumTotalDistance(test.robots, test.factories);
        if (test.returnedOutput == test.expectedOutput) {
            cout << "\e[32;m  => Pass\n";
        } else {
            cout << "\e[31;m  => Failed : returned " << test.returnedOutput << "\n";
        }
        cout << "\e[0;m\n";
    }

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\nElapsed = " << elapsed.count() << "ms\n";
}
