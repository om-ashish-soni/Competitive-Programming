// problem link : https://leetcode.com/problems/sort-list/
// solution : below code
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
    
    ListNode* sortList(ListNode* head) {
        if(head==NULL) return head;
        if(head->next == NULL) return head;
        head->next=sortList(head->next);
        ListNode* curr=head->next;
        ListNode* prev=head;
        while(curr && head->val > curr->val){
            prev=curr;
            curr=curr->next;
        }
        if(prev != head){
            prev->next=head;
            ListNode* newHead=head->next;
            head->next=curr;
            return newHead;
        }
        return head;
    }
};
