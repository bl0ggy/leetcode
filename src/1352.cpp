#include "common.h"

// Naive, slow
class ProductOfNumbers {
    vector<int> nums;

  public:
    ProductOfNumbers() {
    }

    void add(int num) {
        nums.push_back(num);
    }

    int getProduct(int k) {
        int i = nums.size();
        int product = 1;
        while (k > 0) {
            product *= nums[i - k];
            k--;
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
