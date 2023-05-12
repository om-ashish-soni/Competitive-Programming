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
    map<int,int> hashTable;
    void preOrder(TreeNode* root){
        if(!root) return;
        hashTable[root->val]++;
        preOrder(root->left);
        preOrder(root->right);
        return;
    }
    vector<int> findMode(TreeNode* root) {
        preOrder(root);
        vector<int> output;
        int mx=0;
        for(auto node:hashTable){
            mx=max(mx,node.second);
        }
        for(auto node:hashTable){
            if(mx==node.second){
                output.push_back(node.first);
            }
        }
        hashTable.clear();
        return output;
    }
};