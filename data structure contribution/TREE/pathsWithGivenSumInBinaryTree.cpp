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
    void pathSum(TreeNode* root,int targetSum,int &ctr,int sum=0){
        if(!root) return;
        sum+=root->val;
        if(targetSum==sum){
            ctr++;
        }
        pathSum(root->left,targetSum,ctr,sum);
        pathSum(root->right,targetSum,ctr,sum);
        return;
    }
    int pathSum(TreeNode* root, int targetSum) {
        int ctr=0;
        int mx_ctr=0;
        if(!root) return ctr;
        pathSum(root,targetSum,ctr);
        mx_ctr+=ctr;
        mx_ctr+=pathSum(root->left,targetSum);
        mx_ctr+=pathSum(root->right,targetSum);
        return mx_ctr;
    }
};