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
    string tree2str(TreeNode* root) {
        string s;
        if(!root) return s;
        stringstream tempStr;
        tempStr<<root->val;
        s+=tempStr.str();
        s+=((root->left)?("("+tree2str(root->left)+")"):(""));
        s+=(root->right && !root->left)?("()"):("");
        s+=((root->right)?("("+tree2str(root->right)+")"):(""));
        return s;
    }
};