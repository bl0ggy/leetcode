#include "common.h"

class Solution {
  public:
    TreeNode *recoverFromPreorder(string traversal) {
        int rootValue = atoi(traversal.c_str());
        TreeNode *root = new TreeNode(rootValue);

        stack<TreeNode *> nodes;
        nodes.push(root);

        size_t length = traversal.length();
        size_t dashCount = 0;
        for (size_t i = traversal.find('-'); i < length; i++) {
            char c = traversal[i];
            if (c == '-') {
                dashCount++;
            } else {
                while (nodes.size() > dashCount) {
                    nodes.pop();
                }
                dashCount = 0;
                int value = atoi(traversal.c_str() + i);
                TreeNode *node = new TreeNode(value);
                TreeNode *parent = nodes.top();
                if (parent->left == nullptr) {
                    parent->left = node;
                } else {
                    parent->right = node;
                }
                nodes.push(node);
                i = traversal.find('-', i) - 1;
            }
        }

        return root;
    }
};

int main() {
    TestSuite<TreeNode *, string> testSuite("Recovered tree", "traversal");
    testSuite.addTestCases({
        // Original test cases
        {
            stringToTreeNode("[1,2,5,3,4,6,7]"),
            "1-2--3--4-5--6--7",
        },
        {
            stringToTreeNode("[1,2,5,3,null,6,null,4,null,7]"),
            "1-2--3---4-5--6---7",
        },
        {
            stringToTreeNode("[1,401,null,349,88,90]"),
            "1-401--349---90--88",
        },
        // Submission test cases
        // My test cases
    });

    Main main;
    main.runTests(&Solution::recoverFromPreorder, testSuite);
}
