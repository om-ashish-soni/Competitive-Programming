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
    ListNode* head;
    int size=0;
    Solution(ListNode* thead) {
        this->head=thead;
        while(thead ) {thead=thead->next;size++;}
    }
    
    int getRandom() {
        int nthNode=rand();
        nthNode%=size;
        ListNode* curr=head;
        while(curr && nthNode>0){
            curr=curr->next;
            nthNode--;            
        }
        return curr->val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */