#include "common.h"

// Faster but still slow
class ProductOfNumbers {
    vector<int> nums;
    int index = -1;
    bool full = false;

  public:
    ProductOfNumbers() {
        nums.resize(40001);
    }

    void add(int num) {
        if (num == 0) {
            index = -1;
            full = false;
            return;
        }

        index++;
        if (index >= 40001) {
            index = 0;
            full = true;
        }
        nums[index] = num;
        cout << index << " " << num << endl;
    }

    int getProduct(int k) {
        int product = 1;
        if (full) {
            for (int i = 0; i < 40001; i++) {
                product *= nums[i];
            }
        } else if (k > index + 1) {
            return 0;
        } else {
            for (int i = index; i > index - k; i--) {
                product *= nums[i];
            }
        }
        return product;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

class Solution {
  public:
    vector<int> main(vector<string> actions, vector<vector<int>> inputs) {
        ProductOfNumbers *obj;
        vector<int> ans;
        for (int i = 0; i < actions.size(); i++) {
            if (actions[i] == "ProductOfNumbers") {
                obj = new ProductOfNumbers();
            } else if (actions[i] == "add") {
                obj->add(inputs[i][0]);
            } else if (actions[i] == "getProduct") {
                ans.push_back(obj->getProduct(inputs[i][0]));
            }
        }

        return ans;
    }
};

int main() {
    TestSuite<vector<int>, vector<string>, vector<vector<int>>> testSuite("two sum", "values", "target");
    testSuite.addTestCases({
        // Original test cases
        {
            {20, 40, 0, 32}, // {null,null,null,null,null,null,20,40,0,null,32}
            {"ProductOfNumbers", "add", "add", "add", "add", "add", "getProduct", "getProduct", "getProduct", "add", "getProduct"},
            {{}, {3}, {0}, {2}, {5}, {4}, {2}, {3}, {4}, {8}, {2}},
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::main, testSuite);
}
