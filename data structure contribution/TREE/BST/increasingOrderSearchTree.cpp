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
    void inOrder(TreeNode* root,vector<TreeNode*> &v){
        if(!root) return ;
        inOrder(root->left,v);
        v.push_back(root);
        inOrder(root->right,v);
        return ;
    }
    TreeNode* increasingBST(TreeNode* root) {
        vector<TreeNode*> v;
        inOrder(root,v);
        for(int i=1;i<v.size();i++){
            v[i-1]->left=NULL;
            v[i-1]->right=v[i];
        }
        v[v.size()-1]->left=NULL;
        v[v.size()-1]->right=NULL;
        return v[0];
    }
};