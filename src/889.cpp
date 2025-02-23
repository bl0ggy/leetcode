#include "common.h"

class Solution {
  public:
    TreeNode *constructFromPrePost(vector<int> &preorder, vector<int> &postorder) {
        int size = preorder.size();
        TreeNode *root = new TreeNode(preorder[0]);
        unordered_map<int, TreeNode *> valueToNode;
        valueToNode[preorder[0]] = root;
        TreeNode *currentNode = root;
        int left = 1;
        while (left < size) {
            const int val = preorder[left];
            currentNode->left = new TreeNode(val);
            currentNode = currentNode->left;
            valueToNode[val] = currentNode;
            left++;
        }

        stack<TreeNode *> post;
        post.push(root);
        int right = size - 2;
        while (right >= 0) {
            const int val = postorder[right];
            const auto nodeVal = valueToNode[val];
            auto top = post.top();

            TreeNode *parent;
            while ((parent = findChildParent(top, nodeVal)) == nullptr) {
                post.pop();
                top = post.top();
            }

            if (top->left == nodeVal) {
                post.push(nodeVal);
                right--;
                continue;
            }

            if (parent->left == nodeVal) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            top->right = nodeVal;
            post.push(nodeVal);
            right--;
        }

        return root;
    }

    TreeNode *findChildParent(TreeNode *parent, TreeNode *child) {
        deque<TreeNode *> q;
        q.push_front(parent);
        while (q.size()) {
            const auto top = q.front();
            q.pop_front();
            if (top == nullptr) {
                continue;
            }

            if (top->left == child) {
                return top;
            }
            q.push_front(top->left);
            q.push_front(top->right);
        }

        return nullptr;
    }
};

int main() {
    TestSuite<TreeNode *, vector<int>, vector<int>> testSuite("Tree node", "preorder", "postorder");
    testSuite.addTestCases({
        // Original test cases
        {
            stringToTreeNode("[1,2,3,4,5,6,7]"),
            {1, 2, 4, 5, 3, 6, 7},
            {4, 5, 2, 6, 7, 3, 1},
        },
        {
            stringToTreeNode("[1]"),
            {1},
            {1},
        },
        // Submission test cases
        // My test cases
        {
            stringToTreeNode("[1,2,5,3,4,6,null,null,null,7]"),
            {1, 2, 3, 4, 7, 5, 6},
            {3, 7, 4, 2, 6, 5, 1},
        },
        {
            stringToTreeNode("[1,2,3,4,5,6,7,8,null,null,null,10,null,null,null,9,null,11]"),
            {1, 2, 4, 8, 9, 5, 3, 6, 10, 11, 7},
            {9, 8, 4, 5, 2, 11, 10, 6, 7, 3, 1},
        },
    });

    Main main;
    main.runTests(&Solution::constructFromPrePost, testSuite);
}
