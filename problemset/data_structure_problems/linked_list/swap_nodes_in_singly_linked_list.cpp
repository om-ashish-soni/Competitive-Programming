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
    void lengthOfLinkedList(ListNode* head,int &len){
        if(!head) return;
        lengthOfLinkedList(head->next,++len);
    }
    ListNode* swapNodes(ListNode* head, int k) {
        int len=0;
        lengthOfLinkedList(head,len);
        if(k>(len+1)/2){
            k=len+1-k;
        }
        ListNode* dummy=new ListNode();
        dummy->next=head;
        ListNode* curr=dummy;
        ListNode* next=dummy;
        ListNode* pred=dummy;
        for(int i=0;i<k;i++){
            next=next->next;
        }
        for(int i=0;i<k;i++){
            pred=curr;
            curr=curr->next;
            next=next->next;
        }
        ListNode* pred1=pred;
        ListNode* node1=curr;
        if(!next){
            return head;
        }
        ListNode* pred2=curr;
        while(next){
            pred2=curr;
            curr=curr->next;
            next=next->next;
        }
        ListNode* node2=curr;
        if(pred1->next == pred2){
            ListNode* temp=pred1->next;
            pred1->next=pred2->next;
            temp->next=node2->next;
            node2->next=temp;
            return dummy->next;
        }
        pred1->next=pred1->next->next;
        pred2->next=pred2->next->next;
        node2->next=pred1->next;
        node1->next=pred2->next;
        pred1->next=node2;
        pred2->next=node1;
        return dummy->next;
    }
};