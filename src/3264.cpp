#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier) {
        for (int i = 0; i < k; i++) {
            auto it = min_element(nums.begin(), nums.end());
            *it = *it * multiplier;
        }

        return nums;
    }
};

struct TestCase {
    vector<int> input;
    int k;
    int multiplier;
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
    cout << "Input: ";
    print(test.input);
    cout << "}\nOutput: ";
    print(test.expectedOutput);
    cout << "\n";
}

int main() {
    vector<TestCase> testCases{
        {
            .input = {2, 1, 3, 5, 6},
            .k = 5,
            .multiplier = 2,
            .expectedOutput = {8, 4, 6, 5, 6},
        },
        {
            .input = {1, 2},
            .k = 3,
            .multiplier = 4,
            .expectedOutput = {16, 8},
        },
    };

    auto start = chrono::system_clock::now();
    for (auto test : testCases) {
        printFlatten(test);
        Solution solution;
        test.returnedOutput = solution.getFinalState(test.input, test.k, test.multiplier);
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
