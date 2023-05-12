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
    int maxPathSum(TreeNode* root,int &mx){
        if(!root) return 0;
        int self=root->val;
        int left=maxPathSum(root->left,mx);
        int right=maxPathSum(root->right,mx);
        mx=max(self,max(mx,max(max(self+left,self+right),self+right+left)));
        
        return max(self,max(self+left,self+right));
    }
    int maxPathSum(TreeNode* root) {
        int mx=-1001;
        maxPathSum(root,mx);
        return mx;
    }
};