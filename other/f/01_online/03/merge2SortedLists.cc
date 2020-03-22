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

// without splice
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *tmp=NULL, *head;

        if(!l1) {
            return l2;
        }

        if(!l2) {
            return l1;
        }

        if(l1->val < l2->val) {
            tmp = l1;
            l1 = l1->next;
        } else {
            tmp = l2;
            l2 = l2->next;
        }

        head = tmp;

        while(l1 && l2) {
            if(l1->val < l2->val) {
                tmp->next = l1;
                tmp = tmp->next;
                l1 = l1->next;
            } else {
                tmp->next = l2;
                tmp = tmp->next;
                l2 = l2->next;
            }
        }

        while(l1) {
            tmp->next = l1;
            tmp = tmp->next;
            l1 = l1->next;
        }

        while(l2) {
            tmp->next = l2;
            tmp = tmp->next;
            l2 = l2->next;
        }

        return head;
    }
};

// with splice
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
