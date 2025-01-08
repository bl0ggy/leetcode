#include "common.h"

class Solution {
  public:
    // For each node, check if they're nullptr or not,
    // then recurse their children with both flipped and unflipped
    // O(n)
    bool flipEquiv(TreeNode *a, TreeNode *b) {
        if (a == nullptr && b == nullptr) {
            return true;
        } else if (a != nullptr && b != nullptr) {
            bool caseSame = flipEquiv(a->left, b->left) && flipEquiv(a->right, b->right);
            bool caseFlip = flipEquiv(a->left, b->right) && flipEquiv(a->right, b->left);
            return a->val == b->val && (caseSame || caseFlip);
        } else { // Only one is nullptr
            return false;
        }
    }
};

int main() {
    TestSuite<bool, TreeNode *, TreeNode *> testSuite("both equivalent", "root 1", "root 2");
    testSuite.addTestCases({
        // Original test cases
        {
            true,
            stringToTreeNode("[1,2,3,4,5,6,null,null,null,7,8]"),
            stringToTreeNode("[1,2,3,4,5,6,null,null,null,7,8]"),
        },
        {
            true,
            stringToTreeNode("[]"),
            stringToTreeNode("[]"),
        },
        {
            false,
            stringToTreeNode("[]"),
            stringToTreeNode("[1]"),
        },
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::flipEquiv, testSuite);
}
