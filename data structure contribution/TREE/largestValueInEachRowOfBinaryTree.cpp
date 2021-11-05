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
    void largestValues(TreeNode* root,vector<int> &row,int level=0){
        if(!root) return;
        if(row.size()>level){
            row[level]=max(row[level],root->val);
        }else{
            row.push_back(root->val);
        }
        largestValues(root->left,row,1+level);
        largestValues(root->right,row,1+level);
        return;
    } 
    vector<int> largestValues(TreeNode* root) {
        vector<int> row;
        largestValues(root,row);
        return row;
    }
};