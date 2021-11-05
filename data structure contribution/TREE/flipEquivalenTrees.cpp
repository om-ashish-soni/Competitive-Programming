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
    bool isSame(TreeNode* root1,TreeNode* root2){
        if(!root1 && !root2) return true;
        if(root1 && root2){
            if(root1->val == root2->val) return true;
        }
        return false;
    }
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2) return true;
        return isSame(root1,root2) && ((flipEquiv(root1->left,root2->left) && flipEquiv(root1->right,root2->right)) || (flipEquiv(root1->left,root2->right)&& flipEquiv(root1->right,root2->left)));
    }
};