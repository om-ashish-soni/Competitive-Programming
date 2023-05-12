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
    bool isSubTreeUtil(TreeNode* root,TreeNode* subRoot){
        if(!root && !subRoot) return true;
        if(!root || !subRoot) return false;
        if(root->val == subRoot->val){
            return isSubTreeUtil(root->left,subRoot->left) && isSubTreeUtil(root->right,subRoot->right);
        }
        return false;
    }
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if(!root && !subRoot) return true;
        if(!root || !subRoot) return false;
        if(isSubTreeUtil(root,subRoot)){
            return true;
        }
        if(root->left && root->right) return isSubtree(root->left,subRoot) || isSubtree(root->right,subRoot);
        if(root->left) return isSubtree(root->left,subRoot);
        return  isSubtree(root->right,subRoot);
    }
};