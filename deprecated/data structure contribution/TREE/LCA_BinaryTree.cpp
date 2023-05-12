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
    bool pathOfNode(TreeNode* root,int val,vector<TreeNode*> &v){
        if(!root) return false;
        
        if(root->val == val){ return true;}
        bool left=pathOfNode(root->left,val,v);
        bool right=pathOfNode(root->right,val,v);
        if(left) v.push_back(root->left);
        if(right) v.push_back(root->right);
        return left||right;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> first;
        vector<TreeNode*> second;
        pathOfNode(root,p->val,first);
        pathOfNode(root,q->val,second);
        first.push_back(root);
        second.push_back(root);
        reverse(first.begin(),first.end());
        reverse(second.begin(),second.end());
        TreeNode* common=NULL;
        for(int i=0;i<min(first.size(),second.size());i++){
            if(first[i]==second[i]){
                common=first[i];
            }else break;
        }
        return common;
    }
};