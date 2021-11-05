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
     ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* newHead=reverseList(head->next);
        ListNode* nextNext=head->next->next;
        head->next->next=head;
        head->next=nextNext;
        return newHead;
    }
    ListNode* middleNode(ListNode* head) {
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        if(!fast) return slow;
        return slow->next;
    }
    void reorderList(ListNode* head) {
        ListNode* mid=middleNode(head);
        mid=reverseList(mid);
        while(mid){
            ListNode* tempHead=head->next;
            ListNode* tempMid=mid->next;
            head->next=mid;
            mid->next=tempHead;
            head=tempHead;
            mid=tempMid;
        }
        if(head){
            head->next=NULL;
        }
        return;
    }
};