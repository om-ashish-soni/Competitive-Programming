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
    bool isLeaf(TreeNode* root){
        if(!root) return false;
        return !root->left && !root->right;
    }
    void flatten(TreeNode* root) {
        if(!root) return;
        if(isLeaf(root->left) && isLeaf(root->right)){
            TreeNode* temp=root->right;
            root->right=root->left;
            root->right->right=temp;
            root->left=NULL;
            return;
        }else if(isLeaf(root->left)){
            TreeNode* temp=root->right;
            root->right=root->left;
            root->right->right=temp;
            root->left=NULL;
            
        }
            
        flatten(root->left);
        TreeNode* edgeLast=root->left;
        if(edgeLast){
            while(edgeLast->right){
                edgeLast=edgeLast->right;
            }
            TreeNode* temp=root->right;
            root->right=root->left;
            edgeLast->right=temp;
            root->left=NULL;
        }
        flatten(root->right);
    }
};