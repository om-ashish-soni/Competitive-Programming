// Problem link : https://leetcode.com/problems/diameter-of-binary-tree/
// Solution : below code

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
    pair<int,int> diaOfTree(TreeNode* root){
        if(!root) return {0,0};
        pair<int,int> left,right,self;
        left=diaOfTree(root->left);
        right=diaOfTree(root->right);
        self.second=max(left.second,right.second)+1;
        self.first=max(left.first,max(right.first,left.second+right.second+1));
        return self;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        pair<int,int> pr=diaOfTree(root);
        return pr.first-1;
    }
};
