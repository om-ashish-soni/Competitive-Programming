// problem link : https://leetcode.com/problems/validate-binary-search-tree/
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
    bool check(TreeNode* root,long long mn,long long mx){
        if(!root) return true;
        if(mn>=root->val || mx<=root->val) return false;
        return check(root->left,mn,root->val) && check(root->right,root->val,mx);
    }
    bool isValidBST(TreeNode* root) {
        long long mn=LLONG_MIN;
        long long mx=LLONG_MAX;
        return check(root,mn,mx);
    }
};
