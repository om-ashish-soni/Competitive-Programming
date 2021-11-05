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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB) return NULL;
        ListNode* ha=headA;
        ListNode* hb=headB;
        ListNode* tailA=NULL,*tailB=NULL;
        while(headA != headB){
            if(headA && !headA->next){tailA=headA;}
            if(headB && !headB->next){tailB=headB;}
            if(tailA && tailB){
                if(tailA!=tailB) return NULL;
            }
            headA=headA->next;
            headB=headB->next;
            if(!headA) headA=hb;
            if(!headB) headB=ha;
        }
        return headA;
    }
};