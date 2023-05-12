// problem link : https://leetcode.com/problems/rotate-list/
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
    int len(ListNode* head){
        int n=0;
        while(head){
            n++;
            head=head->next;
        }
        return n;
    }
    ListNode* rotateRight(ListNode* head, int k) {
        int n=len(head);
        if(n<2) return head;
        k=k%n;
        if(k>0){
            ListNode* left=head,*right=head;
            while(k){
                right=right->next;
                k--;
            }
            while(right->next){
                left=left->next;
                right=right->next;
            }
            right->next=head;
            head=left->next;
            left->next=NULL;
        }
        return head;
    }
};
