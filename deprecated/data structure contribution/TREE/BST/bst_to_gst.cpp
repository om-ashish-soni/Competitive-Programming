// problem link : https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
// solution : below code

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
    int sum=0;
    void gst(TreeNode* root){
        if(!root) return;
        gst(root->right);
        sum+=root->val;
        root->val=sum;
        gst(root->left);
        return;
    }
    TreeNode* bstToGst(TreeNode* root) {
        sum=0;
        gst(root);
        return root;
    }
};
