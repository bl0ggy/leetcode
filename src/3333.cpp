
#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
    int k;
    vector<int> longPresses; // first: first char press, second: amount of repeated chars (not including first char)
    int totalRepeatedLetters = 0;
    int staticLetters;
    long long words = 0;

  public:
    int possibleStringCount(string word, int k) {
        this->k = k;
        bool repeating = false;
        for (int i = 1; i < word.length(); i++) {
            if (word[i - 1] == word[i]) {
                if (!repeating) {
                    longPresses.push_back(1);
                    repeating = true;
                } else {
                    longPresses.back()++;
                }
                // } else {
                //     longPresses.back().first = i;
            } else {
                if (repeating) {
                    totalRepeatedLetters += longPresses.back();
                }
                repeating = false;
            }
        }
        if (repeating) {
            totalRepeatedLetters += longPresses.back();
        }
        staticLetters = word.length() - totalRepeatedLetters;

        // print(longPresses);
        // cout << endl;
        // cout << "totalRepeatedLetters=" << totalRepeatedLetters << endl;
        // cout << "staticLetters=" << staticLetters << endl;

        // long long size = getSize(longPresses, 0, 0);
        getSize(0, 0);

        // long long sizeLongPresses = longPresses.size();
        // vector<vector<int>> dp(sizeLongPresses + 1, vector<int>(sizeLongPresses, 0));
        // for (int i = sizeLongPresses; i >= 0; i--) {
        //     for(int j = i
        // }
        //
        return words;
    }

    void getSize(int index, long long currentSize) {
        if (index > longPresses.size()) {
            return;
        }
        // cout << "getSize " << index << " " << currentSize << endl;
        if (index == longPresses.size()) {
            if (currentSize + staticLetters >= k) {
                words++;
            }
        } else {
            for (int i = 0; i <= longPresses[index]; i++) {
                // sum +=
                getSize(index + 1, currentSize + i);
                // if(currentSize >= k) {
                //     return
                // }
            }
        }
        // return getSize(longPresses, ) + getSize();
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
    string word;
    int k;
    int expectedOutput;
    int returnedOutput;
};

void printTest(TestCase test) {
    cout << "word: " << test.word << "\nk=" << test.k << "\nOutput: " << test.expectedOutput << endl;
}

int main() {
    vector<TestCase> testCases{
        // Original test cases
        {
            .word = "aabbccdd",
            .k = 7,
            .expectedOutput = 5,
        },
        {
            .word = "aabbccdd",
            .k = 8,
            .expectedOutput = 1,
        },
        {
            .word = "aaabbb",
            .k = 3,
            .expectedOutput = 8,
        },
        // My test cases
        {
            .word = "abbcccc",
            .k = 6,
            .expectedOutput = 3,
        },
        {
            .word = "abcd",
            .k = 1,
            .expectedOutput = 1,
        },
        {
            .word = "aaaa",
            .k = 2,
            .expectedOutput = 3,
        },
        {
            .word = "aabbbccccdddddefghijj",
            .k = 19,
            .expectedOutput = 19,
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printTest(test);
        Solution solution;
        test.returnedOutput = solution.possibleStringCount(test.word, test.k);
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
