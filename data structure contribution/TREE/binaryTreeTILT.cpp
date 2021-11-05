/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right0(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int findTilt(TreeNode* root,int &sum) {
        if(!root) return 0;
        int left=findTilt(root->left,sum);
        int right=findTilt(root->right,sum);
        sum+=abs(right-left);
        return left+right+root->val;
    }
    int findTilt(TreeNode* root) {
        int sum=0;
        findTilt(root,sum);
        return sum;
    }
};