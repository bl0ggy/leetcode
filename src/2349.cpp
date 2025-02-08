#include "common.h"

class NumberContainers {
    unordered_map<int, int> indexToValue;
    unordered_map<int, set<int>> valueToIndex;

  public:
    NumberContainers() {
    }

    void change(int index, int number) {
        if (indexToValue[index] != 0) {
            valueToIndex[indexToValue[index]].erase(index);
        }
        indexToValue[index] = number;
        valueToIndex[number].insert(index);
    }

    int find(int number) {
        return valueToIndex[number].size() == 0 ? -1 : *valueToIndex[number].begin();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

class Solution {
  public:
    vector<int> main(vector<string> actions, vector<vector<int>> operands) {
        vector<int> ans;
        NumberContainers *numberContainers = nullptr;
        int operandIndex = 0;
        for (auto action : actions) {
            if (action == "NumberContainers") {
                numberContainers = new NumberContainers();
            } else if (action == "find" && numberContainers != nullptr) {
                int number = operands[operandIndex][0];
                ans.push_back(numberContainers->find(number));
            } else if (action == "change" && numberContainers != nullptr) {
                int index = operands[operandIndex][0];
                int number = operands[operandIndex][1];
                numberContainers->change(index, number);
            }
            operandIndex++;
        }

        delete numberContainers;

        return ans;
    }
};

int main() {
    TestSuite<vector<int>, vector<string>, vector<vector<int>>> testSuite("two sum", "values", "target");
    testSuite.addTestCases({
        // Original test cases
        {
            {-1, 1, 2},
            {"NumberContainers", "find", "change", "change", "change", "change", "find", "change", "find"},
            {{}, {10}, {2, 10}, {1, 10}, {3, 10}, {5, 10}, {10}, {1, 20}, {10}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::main, testSuite);
}
