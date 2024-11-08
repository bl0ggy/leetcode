#include "common.h"
#include "treenode.h"

class Solution {
    vector<int> queriesMax;
    int currentMax;

  public:
    vector<int> treeQueries(TreeNode *root, vector<int> &queries) {
        int querySize = queries.size();
        queriesMax.resize(100001);

        currentMax = 0;
        measureHeightLeftToRight(root, 0);
        currentMax = 0;
        measureHeightRightToLeft(root, 0);

        vector<int> out(querySize);
        for (int i = 0; i < querySize; i++) {
            out[i] = queriesMax[queries[i]];
        }
        return out;
    }

    void measureHeightLeftToRight(TreeNode *node, int depth) {
        if (node == nullptr) {
            return;
        }

        queriesMax[node->val] = currentMax;
        currentMax = max(depth, currentMax);

        measureHeightLeftToRight(node->left, depth + 1);
        measureHeightLeftToRight(node->right, depth + 1);
    }

    void measureHeightRightToLeft(TreeNode *node, int depth = 0) {
        if (node == nullptr) {
            return;
        }

        queriesMax[node->val] = max(queriesMax[node->val], currentMax);
        currentMax = max(depth, currentMax);

        measureHeightRightToLeft(node->right, depth + 1);
        measureHeightRightToLeft(node->left, depth + 1);
    }
};

int main() {
    TestSuite<vector<int>, TreeNode *, vector<int>> testSuite("binary tree sizes", "binary tree", "removal queries");
    testSuite.addTestCases({
        // Original test cases
        {
            {2},
            stringToTreeNode("[1,3,4,2,null,6,5,null,null,null,null,null,7]"),
            {4},
        },
        {
            {3, 2, 3, 2},
            stringToTreeNode("[5,8,9,2,1,3,7,4,6]"),
            {3, 2, 4, 8},
        },
    });

    Main main;
    return main.runTests(&Solution::treeQueries, testSuite);
}
