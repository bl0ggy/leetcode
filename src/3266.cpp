#include <cassert>
#include <chrono>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
    long long mod = 1e9 + 7;

  public:
    long long modpow(long long base, long long exp, long long modulus) {
        long long res = 1;
        base = base % modulus;
        if (base == 0)
            return 0;
        while (exp > 0) {
            if (exp & 1)
                res = (res * base) % modulus;
            exp = exp >> 1; // y = y/2
            base = (base * base) % modulus;
        }
        return res;
    }
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier) {
        if (multiplier == 1) {
            return nums;
        }

        size_t size = nums.size();
        long long maxValue = 0;
        priority_queue<pair<uint64_t, size_t>, vector<pair<uint64_t, size_t>>, greater<pair<uint64_t, size_t>>> sortedNums;
        for (int i = 0; i < nums.size(); i++) {
            if (maxValue < nums[i]) {
                maxValue = nums[i];
            }
            sortedNums.push({nums[i], i});
        }

        while (k > 0 && sortedNums.top().first * multiplier <= maxValue) {
            auto [value, index] = sortedNums.top();
            sortedNums.pop();
            sortedNums.push({value * multiplier, index});
            k--;
        }

        int rounds = k / size;
        int extra = k % size;
        vector<int> answer(size, 0);
        while (sortedNums.size() != 0) {
            auto num = sortedNums.top();
            sortedNums.pop();
            long long e = (num.first * modpow(multiplier, rounds + (extra > 0), mod)) % mod;
            answer[num.second] = e;
            extra--;
        }

        return answer;
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
            .input = {161209470},
            .k = 56851412,
            .multiplier = 39846,
            .expectedOutput = {198168519},
        },
        {
            .input = {2, 1, 3, 5, 6},
            .k = 5,
            .multiplier = 2,
            .expectedOutput = {8, 4, 6, 5, 6},
        },
        {
            .input = {100000, 2000},
            .k = 2,
            .multiplier = 1000000,
            .expectedOutput = {999999307, 999999993},
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
