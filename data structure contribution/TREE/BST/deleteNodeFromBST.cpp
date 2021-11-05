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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return root;
        if(root->val == key){
            TreeNode* curr=root;
            if(!root->left){
                return root->right;
            }if(!root->right){
                return root->left;
            }
            TreeNode* pred=root->right;
            curr=pred->left;
            if(!curr){
                pred->left=root->left;
                return pred;
            }
            while(curr->left){
                pred=curr;
                curr=curr->left;
            }
            pred->left=curr->right;
            curr->left=root->left;
            curr->right=root->right;
            return curr;
        }
        root->left=deleteNode(root->left,key);
        root->right=deleteNode(root->right,key);
        return root;
    }
};