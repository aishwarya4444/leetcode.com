/*

https://leetcode.com/problems/reorder-list/

Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.

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
public:
  ListNode *reverseList(ListNode *head) {
    ListNode *prev=NULL, *next=NULL, *curr=head;
    if(!head || !head->next) {
      return head;
    }
    while(curr) {
      next=curr->next;
      curr->next=prev;
      prev=curr;
      curr=next;
    }
    return prev;
  }
  void reorderList(ListNode* head) {
    ListNode *p1=head, *p2=head, *tmp;
    if(!head || !head->next) {
      return;
    }
    while(p2 && p2->next) {
      p1=p1->next;
      p2=p2->next->next;
    }
    p2=reverseList(p1);
    p1=head;
    while(p1 && p2) {
      tmp=p1->next;
      p1->next=p2;
      p1=tmp;
      tmp=p2->next;
      p2->next=p1;
      p2=tmp;
    }
    if(p1) {
      p1->next=NULL;
    }
  }
};
