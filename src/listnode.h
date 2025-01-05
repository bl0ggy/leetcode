#pragma once

#include <iostream>
#include <queue>
#include <sstream>
#include <string>

// Definition for a single linked list node.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {
    }
    ListNode(int x) : val(x), next(nullptr) {
    }
    ListNode(int x, ListNode *next) : val(x), next(next) {
    }

    bool operator==(ListNode &l) {
        bool result = this->val == l.val;
        if (this->next == nullptr && l.next == nullptr) {
            return result;
        } else if (this->next == nullptr || l.next == nullptr) {
            return false;
        }
        result &= *this->next == *l.next; // Not efficient for long lists, but enough for coding/testing
        return result;
    }

    ~ListNode() {
        if (next) {
            free(next);
        }
    }
};

ListNode *stringToListNode(std::string s) {
    s = s.substr(1, s.size() - 1); // Remove brackets
    size_t pos = std::string::npos;
    ListNode *root = new ListNode(stoi(s));
    ListNode *previousNode = root;
    while ((pos = s.find(',')) != std::string::npos) {
        s = s.substr(pos + 1);
        ListNode *node = new ListNode(stoi(s));
        previousNode->next = node;
        previousNode = node;
    }
    return root;
}
std::string toString(ListNode *treeNode, bool root = true) {
    std::stringstream ss;
    if (treeNode == nullptr) {
        ss << "[]";
        return ss.str();
    }

    ss << "[" << treeNode->val;
    ListNode *node = treeNode->next;
    while (node) {
        ss << "," << node->val;
        node = node->next;
    }
    ss << "]";
    return ss.str().substr(0, 80);
}
