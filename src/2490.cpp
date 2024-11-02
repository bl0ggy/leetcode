#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    bool isCircularSentence(string sentence) {
        if (sentence.front() == ' ' || sentence.back() == ' ') {
            return false;
        }

        int sentenceLength = sentence.length();
        for (int i = 1; i < sentenceLength - 1; i++) {
            auto pos = sentence.find(' ', i);
            if (pos == string::npos) {
                break;
            }
            if (sentence[pos - 1] != sentence[pos + 1]) {
                return false;
            }
            i = pos;
        }
        return sentence.front() == sentence.back();
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

    void print(vector<pair<int, int>> v) {
        cout << "{";
        for (auto p = v.begin(); p != v.end(); p++) {
            cout << "{" << p->first << "," << p->second << "}";
            if (p + 1 != v.end()) {
                cout << ",";
            }
        }
    }
};

struct TestCase {
    string sentence;
    bool expectedOutput;
    bool returnedOutput;
};

void printTest(TestCase test) {
    cout << "word: " << test.sentence << "\nOutput: " << test.expectedOutput << endl;
}

int main() {
    vector<TestCase> testCases{
        {
            .sentence = "leetcode exercises sound delightful",
            .expectedOutput = true,
        },
        {
            .sentence = "eetcode",
            .expectedOutput = true,
        },
        {
            .sentence = "Leetcode is cool",
            .expectedOutput = false,
        },
        {
            .sentence = "MuFoevIXCZzrpXeRmTssj lYSW U jM",
            .expectedOutput = false,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printTest(test);
        Solution solution;
        test.returnedOutput = solution.isCircularSentence(test.sentence);
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
