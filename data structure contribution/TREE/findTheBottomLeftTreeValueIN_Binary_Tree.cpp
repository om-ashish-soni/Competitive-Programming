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
    void findBottomLeftValue(TreeNode* root,TreeNode *&leftMost,int &currLvl,int level=0){
        if(!root) return;
        if(level>currLvl){
            currLvl=level;
            leftMost=root;
        }
        findBottomLeftValue(root->left,leftMost,currLvl,1+level);
        findBottomLeftValue(root->right,leftMost,currLvl,1+level);
        return;
    }
    int findBottomLeftValue(TreeNode* root) {
        TreeNode* leftMost=NULL;
        int currLvl=-1;
        findBottomLeftValue(root,leftMost,currLvl);
        return leftMost->val;
    }
};