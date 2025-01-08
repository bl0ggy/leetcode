#include "common.h"

class Solution {
  public:
    // BFS recursive
    // With n the amount of nodes: O(n)
    // long long kthLargestLevelSum(TreeNode *root, int k) {
    //     vector<TreeNode *> levelNodes;
    //     vector<long long> sums;
    //     levelNodes.push_back(root);
    //     // sums.push_back(root->val);
    //     bfs(levelNodes, sums);
    //     sort(sums.begin(), sums.end());
    //     // cout << sums.size() << toString(sums) << endl;
    //     if (k > sums.size()) {
    //         return -1;
    //     }
    //     return sums[sums.size() - k];
    // }
    //
    // void bfs(vector<TreeNode *> &levelNodes, vector<long long> &sums) {
    //     vector<TreeNode *> nextLevelNodes;
    //     long long sum = 0;
    //     for (auto n : levelNodes) {
    //         if (n == nullptr) {
    //             continue;
    //         }
    //         sum += n->val;
    //         if (n->left != nullptr) {
    //             nextLevelNodes.push_back(n->left);
    //         }
    //         if (n->right != nullptr) {
    //             nextLevelNodes.push_back(n->right);
    //         }
    //     }
    //     if (levelNodes.size() == 0) {
    //         return;
    //     }
    //     sums.push_back(sum);
    //     bfs(nextLevelNodes, sums);
    // }

    // BFS loop
    // Still O(n) but faster
    long long kthLargestLevelSum(TreeNode *root, int k) {
        vector<TreeNode *> levelNodes, nextLevelNodes;
        vector<long long> sums;
        levelNodes.push_back(root);

        int level = 0;
        while (levelNodes.size() > 0) {
            long long sum = 0;
            nextLevelNodes.clear();
            for (auto n : levelNodes) {
                if (n == nullptr) {
                    continue;
                }
                sum += n->val;
                if (n->left != nullptr) {
                    nextLevelNodes.push_back(n->left);
                }
                if (n->right != nullptr) {
                    nextLevelNodes.push_back(n->right);
                }
            }
            if (levelNodes.size() > 0) {
                sums.push_back(sum);
            }
            std::swap(levelNodes, nextLevelNodes);
            level++;
        }

        if (level < k) {
            return -1;
        }
        sort(sums.begin(), sums.end());
        return sums[sums.size() - k];
    }
};

int main() {
    TestSuite<long long, TreeNode *, int> testSuite("Largest sum", "root", "k");
    testSuite.addTestCases({
        // Original test cases
        {
            13,
            stringToTreeNode("[5,8,9,2,1,3,7,4,6]"),
            2,
        },
        {
            3,
            stringToTreeNode("[1,2,null,3]"),
            1,
        },
        // Submission test cases
        {
            -1,
            stringToTreeNode("[5,8,9,2,1,3,7]"),
            4,
        }
        // My test cases
    });

    Main main;
    return main.runTests(&Solution::kthLargestLevelSum, testSuite);
}
