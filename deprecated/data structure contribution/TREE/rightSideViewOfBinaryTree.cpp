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
    void rightSideView(TreeNode* root,vector<int> &v,int level=0){
        if(!root) return ;
        if(v.size()>level){
            v[level]=root->val;
        }else{
            v.push_back(root->val);
        }
        rightSideView(root->left,v,1+level);
        rightSideView(root->right,v,1+level);
        return;
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> v;
        if(!root) return v;
        rightSideView(root,v);
        return v;
    }
};