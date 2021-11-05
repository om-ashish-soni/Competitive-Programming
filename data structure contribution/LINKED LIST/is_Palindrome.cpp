/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;
    }
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next ) return head;
        ListNode* newHead=reverseList(head->next);
        ListNode* nextNext=head->next->next;
        head->next->next=head;
        head->next=nextNext;
        return newHead;
    }
    bool isPalindrome(ListNode* head) {
        ListNode* middleNode1=reverseList(middleNode(head));
        while(middleNode1){
            if(middleNode1->val != head->val) return false;
            middleNode1=middleNode1->next;
            head=head->next;
        }
        return true;
    }
};