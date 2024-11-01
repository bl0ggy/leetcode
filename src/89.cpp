#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    void gray(vector<int> &input, int level) {
        if (level <= 0) {
            return;
        }
        gray(input, level - 1);
        input.push_back(input.back() ^ (1 << (level - 1)));
        gray(input, level - 1);
    }

    vector<int> grayCode(int n) {
        vector<int> answer;
        answer.reserve(n);
        answer.push_back(0);
        gray(answer, n);

        return answer;
    }

    // Best solution, very smart
    // vector<int> grayCode(int n) {
    //     vector<int> res;
    //     for (int i = 0; i < (1 << n); i++) {
    //         res.push_back(i ^ (i >> 1));
    //         cout << bitset<16>(res.back()) << endl;
    //     }
    //     return res;
    // }
};

struct TestCase {
    int n;
    vector<int> expectedOutput;
    vector<int> returnedOutput;
};

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

void printFlatten(TestCase test) {
    cout << "Input: " << test.n;
    cout << "\nOutput: ";
    print(test.expectedOutput);
    cout << "\n";
}

int main() {
    vector<TestCase> testCases{
        {
            .n = 1,
            .expectedOutput = {0, 1},
        },
        {
            .n = 2,
            .expectedOutput = {0, 1, 3, 2},
        },
        {
            .n = 3,
            .expectedOutput = {0, 1, 3, 2},
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printFlatten(test);
        Solution solution;
        test.returnedOutput = solution.grayCode(test.n);
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
