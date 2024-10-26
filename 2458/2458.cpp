#include <chrono>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {
    }
    TreeNode(TreeNode &node) = delete;
    TreeNode(TreeNode &&node) {
        this->left = node.left;
        this->right = node.right;
    }
    ~TreeNode() {
        cout << "freeing node\n";
        if (left != nullptr)
            free(left);
        if (right != nullptr)
            free(right);
    }
};

class Solution {
  public:
    vector<int> treeQueries(TreeNode *root, vector<int> &queries) {
        int querySize = queries.size();
        vector<int> out(querySize, 0);
        for (int i = 0; i < querySize; i++) {
            out[i] = measureHeight(root, queries[i]) - 1;
        }

        return out;
    }

    int measureHeight(TreeNode *node, int skipValue) {
        if (node == nullptr || node->val == skipValue) {
            return 0;
        }

        int left = measureHeight(node->left, skipValue);
        int right = measureHeight(node->right, skipValue);

        return left > right ? 1 + left : 1 + right;
    }
};

TreeNode *stringToTreeNode(string s) {
    s = s.substr(1, s.size() - 1); // Remove brackets
    queue<TreeNode *> nodes;
    size_t pos = string::npos;
    if (s[0] == 'n') {
        nodes.push(nullptr);
    } else {
        nodes.push(new TreeNode(stoi(s)));
    }
    while ((pos = s.find(',')) != string::npos) {
        s = s.substr(pos + 1);
        if (s[0] == 'n') {
            nodes.push(nullptr);
        } else {
            nodes.push(new TreeNode(stoi(s)));
        }
    }

    // cout << "values: ";
    // for (TreeNode *node : nodes) {
    //     if (node == nullptr) {
    //         cout << "null ";
    //     } else {
    //         cout << node->val << " ";
    //     }
    // }
    // cout << "\n";

    int elementsToTake = 1;
    TreeNode *root;
    queue<TreeNode *> nodesPreviousRow, nodesCurrentRow;
    while (nodes.size() > 0) {
        cout << "nodes\n";
        if (elementsToTake == 1) {
            cout << "elementsToTake=" << elementsToTake << "\n";
            root = nodes.front();
            nodes.pop();
            cout << "a " << root->val << "\n";
            nodesPreviousRow.push(root);
            elementsToTake = nodesPreviousRow.size() * 2;
        } else {
            cout << "elementsToTake=" << elementsToTake << "\n";
            nodesCurrentRow = {};
            for (int i = 0; i < elementsToTake; i++) {
                TreeNode *node = nodes.front();
                nodes.pop();
                nodesCurrentRow.push(node);
            }
            int previousSize = nodesPreviousRow.size();
            for (int i = 0; i < previousSize; i++) {
                if (nodesCurrentRow.front() != nullptr) {
                    TreeNode *left = nodesCurrentRow.front();
                    nodesPreviousRow.front()->left = left;
                    nodesPreviousRow.push(left);
                    cout << nodesPreviousRow.front()->val << " left->" << left->val << "\n";
                    // } else {
                    //     cout << nodesPreviousRow.front()->val << " left->null\n";
                }
                nodesCurrentRow.pop();

                if (nodesCurrentRow.front() != nullptr) {
                    TreeNode *right = nodesCurrentRow.front();
                    nodesPreviousRow.front()->right = right;
                    nodesPreviousRow.push(right);
                    cout << nodesPreviousRow.front()->val << " right->" << right->val << "\n";
                    // } else {
                    //     cout << nodesPreviousRow.front()->val << " right->null\n";
                }
                nodesCurrentRow.pop();
                nodesPreviousRow.pop();
            }
            elementsToTake = nodesPreviousRow.size() * 2;
        }
    }

    return root;
}

int main() {
    string input = "[1,3,4,2,null,6,5,null,null,null,null,null,7]";
    TreeNode *tree = stringToTreeNode(input);
    vector<int> queries{4};

    auto start = chrono::system_clock::now();

    Solution solution;
    vector<int> out = solution.treeQueries(tree, queries);

    auto end = chrono::system_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "out: ";
    for (int i : out) {
        cout << i << " ";
    }
    cout << "elapsed = " << elapsed.count() << "ms\n";
    free(tree);
}
