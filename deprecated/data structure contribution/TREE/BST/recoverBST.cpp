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
    static bool comp(TreeNode* root1,TreeNode* root2){
        return root1->val < root2->val;
    }
    void inorder(TreeNode* root,vector<int> &v){
        if(!root) return;
        inorder(root->left,v);
        v.push_back(root->val);
        inorder(root->right,v);
    }
    void sortedArrayToBST(TreeNode* root,vector<int> &v,int &i){
        if(!root) return;
        sortedArrayToBST(root->left,v,i);
        root->val=v[i];
        i++;
        sortedArrayToBST(root->right,v,i);
        return;
    }
    void recoverTree(TreeNode* root) {
        vector<int > v;
        inorder(root,v);
        sort(v.begin(),v.end());
        int i=0;
        sortedArrayToBST(root,v,i);
        return;
    }
};