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
    TreeNode* addOneRow(TreeNode* root, int val, int depth,int level=1) {
        if(depth == level){
            if(level==1){
                TreeNode* newRoot=new TreeNode;
                newRoot->val=val;
                newRoot->left=root;
                newRoot->right=NULL;
                return newRoot;
            }
            TreeNode* newNode=new TreeNode;
            newNode->val=val;
            return newNode;
        }
        if(!root) return root;
        
            
        
        TreeNode* pastLeft=root->left;
        TreeNode* pastRight=root->right;
        root->left=addOneRow(root->left,val,depth,1+level);
        root->right=addOneRow(root->right,val,depth,1+level);
        if(root->left != pastLeft){
            root->left->left=pastLeft;
            root->left->right=NULL;
            
        }
        if(root->right != pastRight){
            root->right->left=NULL;
            root->right->right=pastRight;
            
        }
        return root;
    }
};