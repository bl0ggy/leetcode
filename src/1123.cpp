#include "common.h"
#include "treenode.h"
#include <thread>

class Solution {
  public:
    TreeNode *lcaDeepestLeaves(TreeNode *root) {
        TreeNode *ans = root;
        int currentMaxDepth = 0;
        set<TreeNode *> nodesAtMaxDepth;
        unordered_map<TreeNode *, pair<TreeNode *, int>> parents; // child,<parent,depth of parent>

        deque<pair<TreeNode *, int>> q; // node, depth
        q.push_front({root, 0});
        while (!q.empty()) {
            auto [node, depth] = q.front();
            q.pop_front();

            if (depth > currentMaxDepth) {
                nodesAtMaxDepth.clear();
                currentMaxDepth = depth;
            }
            if (depth == currentMaxDepth) {
                nodesAtMaxDepth.insert(node);
            }

            if (node->left != nullptr) {
                parents[node->left] = {node, depth};
                q.push_front({node->left, depth + 1});
            }
            if (node->right != nullptr) {
                parents[node->right] = {node, depth};
                q.push_front({node->right, depth + 1});
            }
        }

        if (nodesAtMaxDepth.size() == 1) {
            ans = *nodesAtMaxDepth.begin();
        } else if (nodesAtMaxDepth.size() > 1) {
            while (nodesAtMaxDepth.size() > 1) {
                set<TreeNode *> newNodesAtMaxDepth;
                for (auto n : nodesAtMaxDepth) {
                    newNodesAtMaxDepth.insert(parents[n].first);
                }
                nodesAtMaxDepth = newNodesAtMaxDepth;
            }
            ans = *nodesAtMaxDepth.begin();
        }

        return ans;
    }
};

int main() {
    TestSuite<TreeNode *, TreeNode *> testSuite("Deepest leaves ancestor", "root");
    testSuite.addTestCases({
        // Original test cases
        {
            stringToTreeNode("[2,7,4]"),
            stringToTreeNode("[3,5,1,6,2,0,8,null,null,7,4]"),
        },
        {
            stringToTreeNode("[1]"),
            stringToTreeNode("[1]"),
        },
        {
            stringToTreeNode("[2]"),
            stringToTreeNode("[0,1,3,null,2]"),
        },
        // My test cases
        {
            stringToTreeNode("[1,2,3,4,5,6,7,8,null,null,null,9]"),
            stringToTreeNode("[1,2,3,4,5,6,7,8,null,null,null,9]"),
        },
        {
            stringToTreeNode("[2,4,5,8,null,null,9]"),
            stringToTreeNode("[1,2,3,4,5,6,7,8,null,null,9]"),
        },
        // Submission test cases
    });

    Main main;
    main.runTests(&Solution::lcaDeepestLeaves, testSuite);
}
