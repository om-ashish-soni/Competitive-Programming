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
    int levelOf(TreeNode* root){
        if(!root) return 0;
        return 1+levelOf(root->left);
    }
    void traverse(TreeNode* root,int &n,int &empty,int level=0){
        if(!root) return;
        if(level == n-2){
            if(!root->right) empty++;
            else throw empty; 
            if(!root->left) empty++;
            else throw empty; 
        }
        traverse(root->right,n,empty,1+level);
        traverse(root->left,n,empty,1+level);
    }
    int countNodes(TreeNode* root) {
        if(!root) return 0;
        if(!root->left && !root->right) return 1;
        int level=levelOf(root);
        int no_of_nodes=pow(2,level)-1;
        int ctr=0;
        try{traverse(root,level,ctr);}
        catch(...){ return no_of_nodes-ctr;}
        return no_of_nodes-ctr;
    }
};