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
    bool pathOfNode(TreeNode* root,int val,vector<TreeNode*> &v){
        if(!root) return false;
        
        if(root->val == val){ return true;}
        bool left=pathOfNode(root->left,val,v);
        bool right=pathOfNode(root->right,val,v);
        if(left) v.push_back(root->left);
        if(right) v.push_back(root->right);
        return left||right;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, int p, int q) {
        vector<TreeNode*> first;
        vector<TreeNode*> second;
        pathOfNode(root,p,first);
        pathOfNode(root,q,second);
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
    bool isSibling(TreeNode* root,int x,int y){
        TreeNode* LCA=lowestCommonAncestor(root,x,y);
        if(LCA->left->val == x && LCA->right->val==y) return true;
        if(LCA->left->val ==y && LCA->right->val==x) return true;
        return false;
    }
    int levelOf(TreeNode* root,int val,int level=0){
        if(!root) return 0;
        if(root->val == val) return level;
        int left=levelOf(root->left,val,1+level);
        if(left) return left;
        return levelOf(root->right,val,1+level);
    }
    bool isCousins(TreeNode* root, int x, int y) {
        if((levelOf(root,x) == levelOf(root,y)) && !isSibling(root,x,y)) return true;
        return false;
    }
};