#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

void print(vector<int> vec) {
    cout << "{";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it;
        if (it + 1 != vec.end()) {
            cout << ", ";
        }
    }
    cout << "}";
}

class Solution {
  public:
    vector<int> mostVisited(int n, vector<int> &rounds) {
        vector<int> answer;

        int startingSection = rounds[0];
        vector<int> sections(n);
        sections[0] = startingSection;
        for (int i = 1; i < n; i++) {
            if (sections[i - 1] == n) {
                sections[i] = 1;
            } else {
                sections[i] = sections[i - 1] + 1;
            }
        }
        int totalSectionsStepped = 0;
        for (int i = 1; i < rounds.size(); i++) {
            if (rounds[i] == rounds[i - 1]) {
                totalSectionsStepped += n;
            } else if (rounds[i] > rounds[i - 1]) {
                totalSectionsStepped += rounds[i] - rounds[i - 1];
            } else {
                totalSectionsStepped += rounds[i] + n - rounds[i - 1];
            }
        }

        int remaining = (totalSectionsStepped % n);
        if (remaining == n) {
            return rounds;
        }

        sections.erase(sections.begin() + remaining + 1, sections.end());
        sort(sections.begin(), sections.end());

        return sections;
    }
};

struct TestCase {
    int n;
    vector<int> rounds;
    vector<int> expectedOutput;
    vector<int> returnedOutput;
};

void printFlatten(TestCase test) {
    cout << "n: " << test.n << "\n";
    cout << "rounds: ";
    print(test.rounds);
    cout << "\nOutput: ";
    print(test.expectedOutput);
    cout << "\n";
}

int main() {
    vector<TestCase> testCases{
        {
            .n = 4,
            .rounds = {1, 3, 1, 2},
            .expectedOutput = {1, 2},
        },
        {
            .n = 2,
            .rounds = {2, 1, 2, 1, 2, 1, 2, 1, 2},
            .expectedOutput = {2},
        },
        {
            .n = 7,
            .rounds = {1, 3, 5, 7},
            .expectedOutput = {1, 2, 3, 4, 5, 6, 7},
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printFlatten(test);
        Solution solution;
        test.returnedOutput = solution.mostVisited(test.n, test.rounds);
        if (test.returnedOutput == test.expectedOutput) {
            cout << "\e[32;m  => Pass\n";
        } else {
            cout << "\e[31;m  => Failed : returned ";
            print(test.returnedOutput);
            cout << "\n";
        }
        cout << "\e[0;m\n";
    }

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "\nElapsed = " << elapsed.count() << "ms\n";
}
