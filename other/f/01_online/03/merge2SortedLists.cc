/*

https://leetcode.com/problems/merge-two-sorted-lists/

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

Example:

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    void addEnd(ListNode **head, int num) {
        while(*head) {
            head = &((*head)->next);
        }
        *head = new ListNode(num);
    }

public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *tmp=NULL;

        while(l1 && l2) {
            if(l1->val < l2->val) {
                addEnd(&tmp, l1->val);
                l1 = l1->next;
            } else {
                addEnd(&tmp, l2->val);
                l2 = l2->next;
            }
        }

        while(l1) {
            addEnd(&tmp, l1->val);
            l1 = l1->next;
        }

        while(l2) {
            addEnd(&tmp, l2->val);
            l2 = l2->next;
        }

        return tmp;
    }
};
