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
    void inOrder(TreeNode* root,vector<int> &v){
        if(!root) return;
        inOrder(root->left,v);
        v.push_back(root->val);
        inOrder(root->right,v);
        return;
    }
    int minDiffInBST(TreeNode* root,int diff=INT_MAX) {
        vector<int> output;
        inOrder(root,output);
        sort(output.begin(),output.end());
        diff=output[1]-output[0];
        for(int i=2;i<output.size();i++){
            diff=min(diff,output[i]-output[i-1]);
        }
        return diff;
    }
};