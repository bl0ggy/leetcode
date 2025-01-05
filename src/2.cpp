#include "common.h"

class Solution {
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        bool carry = false;
        ListNode *result = new ListNode();
        ListNode *current = result;
        while (current) {
            int sum = 0;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            if (carry) {
                sum++;
                carry = false;
            }
            if (sum > 9) {
                sum -= 10;
                carry = true;
            }
            current->val = sum;
            if (l1 != nullptr || l2 != nullptr || carry) {
                current->next = new ListNode();
            }
            current = current->next;
        }

        return result;
    }
};

int main() {
    TestSuite<ListNode *, ListNode *, ListNode *> testSuite("sum", "list 1", "list 2");
    testSuite.addTestCases({
        // Original test cases
        {
            stringToListNode("[7, 0, 8]"),
            stringToListNode("[2, 4, 3]"),
            stringToListNode("[5, 6, 4]"),
        },
        {
            stringToListNode("[0]"),
            stringToListNode("[0]"),
            stringToListNode("[0]"),
        },
        {
            stringToListNode("[8, 9, 9, 9, 0, 0, 0, 1]"),
            stringToListNode("[9, 9, 9, 9, 9, 9, 9]"),
            stringToListNode("[9, 9, 9, 9]"),
        },
    });

    Main main;
    return main.runTests(&Solution::addTwoNumbers, testSuite);
}
