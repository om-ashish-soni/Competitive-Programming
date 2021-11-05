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
    ListNode* reverseList(ListNode* head,int n) {
        if(!head || !head->next || n==0) return head;
        ListNode* newHead=reverseList(head->next,n-1);
        ListNode* nextNext=head->next->next;
        head->next->next=head;
        head->next=nextNext;
        return newHead;
    }
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(right==left) return head;
        int diff=right-left;
        ListNode* listHead=new ListNode();
        listHead->next=head;
        int front=left;
        while(--left){ listHead=listHead->next;}
        listHead->next=reverseList(listHead->next,diff);
        if(front==1) return listHead->next; return head;
    }
};