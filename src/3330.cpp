#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    int possibleStringCount(string word) {
        int wordCount = 0;
        for (int i = 1; i < word.length(); i++) {
            if (word[i - 1] == word[i]) {
                wordCount++;
            }
        }

        return wordCount + 1;
    }

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
};

struct TestCase {
    string input;
    int expectedOutput;
    int returnedOutput;
};

void printTest(TestCase test) {
    cout << "Input: " << test.input << "\nOutput: " << test.expectedOutput << endl;
}

int main() {
    vector<TestCase> testCases{
        {
            .input = "abbcccc",
            .expectedOutput = 5,
        },
        {
            .input = "abcd",
            .expectedOutput = 1,
        },
        {
            .input = "aaaa",
            .expectedOutput = 4,
        },
        {
            .input = "aabbbccccdddddefghijj",
            .expectedOutput = 12,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printTest(test);
        Solution solution;
        test.returnedOutput = solution.possibleStringCount(test.input);
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
