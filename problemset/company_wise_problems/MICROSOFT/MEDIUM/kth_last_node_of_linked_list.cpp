// problem link : https://binarysearch.com/problems/Kth-Last-Node-of-a-Linked-List
// solution : below code

/**
 * class LLNode {
 *     public:
 *         int val;
 *         LLNode *next;
 * };
 */
int solve(LLNode* node, int k) {
    int index=0;
    LLNode* fast=node;
    while(index<k){
        index++;
        fast=fast->next;
    }
    LLNode* curr=node;
    while(fast->next){
        curr=curr->next;
        fast=fast->next;
    }
    return curr->val;
}
