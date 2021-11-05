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
    TreeNode* ins(TreeNode* root){
        if(!root->left && !root->right) return NULL;
        if(!root->left) return root->right;
        if(!root->right) return root->left;
        TreeNode* curr=root->right,*pred=root;
        if(!curr->left){
            curr->left=root->left;
            return curr;
        }
        while(curr->left){ pred=curr;curr=curr->left;}
        pred->left=NULL;
        curr->left=root->left;
        return curr;
    }
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if(!root) return NULL;
        root->left=trimBST(root->left,low,high);
        root->right=trimBST(root->right,low,high);
        if(root->val < low || root->val > high) return ins(root);
        return root;
    }
};