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
    int DepthOf(TreeNode* root){
        if(!root) return 0;
        return 1+max(DepthOf(root->left),DepthOf(root->right));
    }
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return -1;
        int left=DepthOf(root->left);
        int right=DepthOf(root->right);
        int mx=left+right;
        mx=max(mx,max(diameterOfBinaryTree(root->left),diameterOfBinaryTree(root->right)));
        return mx;
    }
};