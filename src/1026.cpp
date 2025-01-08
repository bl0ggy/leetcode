#include "common.h"

class Solution {
  private:
    int maxVal = 0;

  public:
    // Recursion
    // With n = height and m = width of the tree: O(n^2*m)
    // For each node and its direct children
    //   - recurse with current parent and direct children of its direct child
    //   - recurse with direct child as parent and direct children of direct child
    // int maxAncestorDiff(TreeNode *root) {
    //     getMax(root, root->left);
    //     getMax(root, root->right);
    //     return maxVal;
    // }
    // void getMax(TreeNode *a, TreeNode *b) {
    //     if (a == nullptr || b == nullptr) {
    //         return;
    //     }
    //     maxVal = max(maxVal, abs(a->val - b->val));
    //     getMax(a, b->left);
    //     getMax(a, b->right);
    //     getMax(b, b->left);
    //     getMax(b, b->right);
    // }

    // Recursion
    // Still O(n^2*m) but faster as we have less recusrion calls thanks to the vector
    // int maxAncestorDiff(TreeNode *root) {
    //     vector<int> parents;
    //     parents.push_back(root->val);
    //     getMax(parents, root);
    //     return maxVal;
    // }
    //
    // void getMax(vector<int> &parents, TreeNode *a) {
    //     if (a == nullptr) {
    //         return;
    //     }
    //
    //     for (auto p : parents) {
    //         maxVal = max(maxVal, abs(p - a->val));
    //     }
    //     parents.push_back(a->val);
    //     getMax(parents, a->left);
    //     getMax(parents, a->right);
    //     parents.pop_back();
    // }

    // Recursion
    // Still O(n^2*m) but even faster as we recurse with only 2 int instead of a whole vector
    int maxAncestorDiff(TreeNode *root) {
        getMax(root, root->val, root->val);
        return maxVal;
    }

    void getMax(TreeNode *root, int mn, int mx) {
        if (root == nullptr) {
            maxVal = max(maxVal, abs(mn - mx));
            return;
        }
        mn = min(mn, root->val);
        mx = max(mx, root->val);
        getMax(root->left, mn, mx);
        getMax(root->right, mn, mx);
    }
};

int main() {
    TestSuite<int, TreeNode *> testSuite("maximum difference", "root");
    testSuite.addTestCases({
        // Original test cases
        {
            7,
            stringToTreeNode("[8,3,10,1,6,null,14,null,null,4,7,13]"),
        },
        {
            3,
            stringToTreeNode("[1,null,2,null,0,3]"),
        },
        // Submission test cases
        {
            4,
            stringToTreeNode("[2,null,0,null,4,null,3,null,1]"),
        },
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::maxAncestorDiff, testSuite);
}
