// problem link : https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/
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
    ListNode* removeZeroSumSublists(ListNode* head) {
        stack<ListNode*> stk;
        int sm=0;
        unordered_map<int,int> hash;
        hash[sm]=1;
        ListNode* tail=head;
        while(tail){
            sm+=tail->val;
            stk.push(tail);
            cout<<"adding "<<tail->val<<endl;
            if(hash.count(sm) && hash[sm]>0){
                int prev=sm;
                do{
                    ListNode* top=stk.top();
                    cout<<"removing "<<top->val<<endl;
                    hash[sm]--;
                    sm-=top->val;
                    stk.pop();
                }while(sm != prev);
                hash[0]++;
            }
            
            hash[sm]++;
            tail=tail->next;
        }
        head=NULL;
        while(stk.size()>0){
            ListNode* top=stk.top();
            top->next=head;
            head=top;
            stk.pop();
        }
        return head;
    }
};
