// problem link : https://leetcode.com/problems/linked-list-in-binary-tree/
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
    map<pair<ListNode*,TreeNode*>,bool> mp;
    bool isSubPath(ListNode* head,TreeNode* root,ListNode* org){
        if(!head) return true;
        if(!root) return false;
        if(head->val==root->val){
            return isSubPath(head->next,root->left,org) or isSubPath(head->next,root->right,org);
        }
        return false;
    }
    bool isSubPath(ListNode* head, TreeNode* root) {
        if(!head) return true;
        if(!root) return false;
        if(root->val==head->val){
            if(isSubPath(head->next,root->left,head) or isSubPath(head->next,root->right,head)) return true;
        }
        return isSubPath(head,root->left) or isSubPath(head,root->right);
    }
};
