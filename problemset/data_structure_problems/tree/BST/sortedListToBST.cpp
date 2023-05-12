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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int lengthOf(ListNode* head){
        if(!head) return 0;
        return 1+lengthOf(head->next);
    }
    ListNode* middle(ListNode* head,int len,int i=0){
        if(!head) return head;
        if(i==len/2) return head;
        return middle(head->next,len,i+1);
    }
    TreeNode* sortedListToBST(ListNode* head,int n=-1) {
        if(!head) return NULL;
        if(n == -1) n=lengthOf(head);
        ListNode* mid=middle(head,n);
        if(n==0){
            return NULL;
        }
        if(n==1){
            TreeNode* root=new TreeNode;
            root->val=head->val;
            root->left=NULL;
            root->right=NULL;
            return root;
        }
        TreeNode* root=new TreeNode;
        root->val=mid->val;
        root->left=sortedListToBST(head,n/2);
        root->right=sortedListToBST(mid->next,n-n/2-1);
        return root;
    }
};