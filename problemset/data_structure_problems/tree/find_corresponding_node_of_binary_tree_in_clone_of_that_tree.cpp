// problem link : https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/
// solution : below code

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
    TreeNode* getTarget(TreeNode* one,TreeNode* two,TreeNode* node){
        if(!one || !two) return NULL;
        if(one==node) return two;
        TreeNode* left=getTarget(one->left,two->left,node);
        if(left and node->val == left->val) return left;
        TreeNode* right=getTarget(one->right,two->right,node);
        if(right and node->val == right->val) return right;
        return NULL;
    }
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        return getTarget(original,cloned,target);
    }
};
