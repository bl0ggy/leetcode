#pragma once

#include <iostream>
#include <queue>
#include <sstream>
#include <string>

// Definition for a binary tree node.
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
        if (left != nullptr) {
            free(left);
        }
        if (right != nullptr) {
            free(right);
        }
    }
};

TreeNode *stringToTreeNode(std::string s) {
    s = s.substr(1, s.size() - 2); // Remove brackets
    if (s.length() == 0) {
        return nullptr;
    }

    std::queue<TreeNode *> nodes;
    size_t pos = std::string::npos;
    if (s[0] == 'n') {
        nodes.push(nullptr);
    } else {
        nodes.push(new TreeNode(stoi(s)));
    }

    while ((pos = s.find(',')) != std::string::npos) {
        s = s.substr(pos + 1);
        if (s[0] == 'n') {
            nodes.push(nullptr);
        } else {
            nodes.push(new TreeNode(stoi(s)));
        }
    }

    int elementsToTake = 1;
    TreeNode *root;
    std::queue<TreeNode *> nodesPreviousRow, nodesCurrentRow;
    while (nodes.size() > 0) {
        if (elementsToTake == 1) {
            root = nodes.front();
            nodes.pop();
            nodesPreviousRow.push(root);
            elementsToTake = nodesPreviousRow.size() * 2;
        } else {
            nodesCurrentRow = {};
            for (int i = 0; i < elementsToTake; i++) {
                if (nodes.size()) {
                    TreeNode *node = nodes.front();
                    nodes.pop();
                    nodesCurrentRow.push(node);
                } else { // We expect other nodes, but trailing "null" are not part of the treenode string
                    nodesCurrentRow.push(nullptr);
                }
            }
            int previousSize = nodesPreviousRow.size();
            for (int i = 0; i < previousSize; i++) {
                if (nodesCurrentRow.front() != nullptr) {
                    TreeNode *left = nodesCurrentRow.front();
                    nodesPreviousRow.front()->left = left;
                    nodesPreviousRow.push(left);
                }
                nodesCurrentRow.pop();

                if (nodesCurrentRow.front() != nullptr) {
                    TreeNode *right = nodesCurrentRow.front();
                    nodesPreviousRow.front()->right = right;
                    nodesPreviousRow.push(right);
                }
                nodesCurrentRow.pop();
                nodesPreviousRow.pop();
            }
            elementsToTake = nodesPreviousRow.size() * 2;
        }
    }

    return root;
}

std::string toString(TreeNode *treeNode, bool root = true) {
    std::stringstream ss;
    std::queue<TreeNode *> nodes;
    nodes.push(treeNode);
    ss << "[";
    while (nodes.size() > 0) {
        TreeNode *front = nodes.front();
        if (front == nullptr) {
            ss << "null";
        } else {
            ss << front->val;
            nodes.push(front->left);
            nodes.push(front->right);
        }
        if (nodes.size() > 1) {
            ss << ",";
        }
        nodes.pop();
    }
    ss << "]";
    return ss.str().substr(0, 80);
}
