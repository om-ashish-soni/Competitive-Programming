// problem link : https://leetcode.com/problems/merge-k-sorted-lists/
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head=NULL;
        ListNode* tail=NULL;
        int ctr=0;
        while(lists.size()>0){
            ListNode* curr=NULL;
            int index=-1;
            vector<ListNode*> &lst=lists;
            vector<int> to_be_removed;
            for(int i=0;i<lists.size();i++){
                if(!lst[i]){
                    to_be_removed.push_back(i);
                    
                }else{
                    if(!curr){
                        curr=lst[i];
                        index=i;
                    }
                    else if((curr->val) > (lst[i]->val)){
                        curr=lst[i];
                        index=i;
                    }
                }
            }
            if(curr){
                if(!head){
                    head=curr;
                    tail=curr;
                }
                else{
                    tail->next=curr;
                    tail=tail->next;
                }
                lst[index]=lst[index]->next;
            }else break;
            
            for(int i=to_be_removed.size()-1;i>=0;i--){
                swap(lst[to_be_removed[i]],lst[lists.size()-1]);
                lst.pop_back();
            } 
            
        }
            
        if(tail) tail->next=NULL;
        return head;
    }
};
