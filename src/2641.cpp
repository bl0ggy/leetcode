#include "common.h"

class Solution {
  public:
    // BFS
    // With n the amount of nodes: O(2*n)
    TreeNode *replaceValueInTree(TreeNode *root) {
        vector<TreeNode *> parentNodes, childNodes;
        vector<int> sums;
        root->val = 0;
        parentNodes.push_back(root);

        while (parentNodes.size() > 0) {
            // First compute the sum of all levels
            childNodes.clear();
            int sum = 0;
            for (auto n : parentNodes) {
                if (n == nullptr) {
                    continue;
                }

                if (n->left != nullptr) {
                    sum += n->left->val;
                    childNodes.push_back(n->left);
                }
                if (n->right != nullptr) {
                    sum += n->right->val;
                    childNodes.push_back(n->right);
                }
            }

            // Then apply the sum - brothers
            for (auto n : parentNodes) {
                int brotherSum = (n->left == nullptr ? 0 : n->left->val) + (n->right == nullptr ? 0 : n->right->val);
                int remainingSum = sum - brotherSum;
                if (n->left != nullptr) {
                    n->left->val = remainingSum;
                }
                if (n->right != nullptr) {
                    n->right->val = remainingSum;
                }
            }

            parentNodes = childNodes;
        }

        return root;
    }
};

int main() {
    TestSuite<TreeNode *, TreeNode *> testSuite("Cousin tree", "root");
    testSuite.addTestCases({
        // Original test cases
        {
            stringToTreeNode("[0,0,0,7,7,null,11]"),
            stringToTreeNode("[5,4,9,1,10,null,7]"),
        },
        {
            stringToTreeNode("[0,0,0]"),
            stringToTreeNode("[3,1,2]"),
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::replaceValueInTree, testSuite);
}
