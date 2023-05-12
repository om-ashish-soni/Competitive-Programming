/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    void pathOfNode(TreeNode* root,int val,vector<TreeNode*> &v){
        if(!root) return ;
        if(root->val == val){ v.push_back(root);return ;}
        if(val<root->val) {v.push_back(root);return pathOfNode(root->left,val,v);}
        if(val>root->val){ v.push_back(root); return pathOfNode(root->right,val,v);}
        return ;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> first;
        vector<TreeNode*> second;
        pathOfNode(root,p->val,first);
        pathOfNode(root,q->val,second);
        TreeNode* common=NULL;
        for(int i=0;i<min(first.size(),second.size());i++){
            if(first[i]==second[i]){
                common=first[i];
            }else break;
        }
        return common;
    }
};