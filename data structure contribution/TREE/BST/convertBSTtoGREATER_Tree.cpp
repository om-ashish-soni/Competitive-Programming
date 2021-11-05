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
    void addOn(TreeNode* root,int sum){
        if(!root) return;
        int temp=root->val;
        root->val+=sum;
        addOn(root->left,root->val-temp);
        addOn(root->right,root->val-temp);
        return;
    }
    int convertIntoBST(TreeNode* root){
        if(!root) return 0;
        int left=convertIntoBST(root->left);
        int right=convertIntoBST(root->right);
        int sum=root->val+left+right;
        root->val += right;
        addOn(root->left,root->val);
        return sum;
    }
    TreeNode* convertBST(TreeNode* root) {
        convertIntoBST(root);
        return root;
    }
};