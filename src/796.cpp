#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    bool rotateString(string s, string goal) {
        int sLength = s.length();
        int goalLength = goal.length();
        if (sLength != goalLength) {
            return false;
        }
        bool found = false;
        for (int i = 0; i < sLength; i++) {
            found = true;
            for (int j = 0; j < sLength; j++) {
                if (s[(i + j) % sLength] != goal[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                break;
            }
        }
        return found;
    }
};

struct TestCase {
    string s;
    string goal;
    bool expectedOutput;
    bool returnedOutput;
};

void printTest(TestCase test) {
    cout << "s: " << test.s << "\ngoal=" << test.goal << "\nOutput: " << test.expectedOutput << endl;
}

int main() {
    vector<TestCase> testCases{
        {
            .s = "abcde",
            .goal = "cdeab",
            .expectedOutput = true,
        },
        {
            .s = "abcde",
            .goal = "abced",
            .expectedOutput = false,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printTest(test);
        Solution solution;
        test.returnedOutput = solution.rotateString(test.s, test.goal);
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
