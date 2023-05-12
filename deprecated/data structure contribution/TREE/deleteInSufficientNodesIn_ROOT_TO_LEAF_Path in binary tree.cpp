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
    TreeNode* deleteNode(TreeNode* root){
        if(!root) return NULL;
        return (!root->left && !root->right)?(NULL):(root);        
    }
    TreeNode* sufficientSubset(TreeNode* root,int &limit,int sum){
        if(!root) return NULL;
        sum+=root->val;
        TreeNode *left=root->left,*right=root->right;
        root->left=sufficientSubset(root->left,limit,sum);
        root->right=sufficientSubset(root->right,limit,sum);
        if(sum < limit ){ return deleteNode(root);}
        if(left != root->left || right != root->right) return deleteNode(root);
        return root;
    }
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        return sufficientSubset(root,limit,0);
    }
};