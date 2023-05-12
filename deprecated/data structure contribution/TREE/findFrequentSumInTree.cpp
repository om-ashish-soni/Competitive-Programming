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
    map<int,int> mp;
    int convertIntoSumTree(TreeNode* root){
        if(!root) return 0;
        if(root->left && root->right) {
            root->val+=convertIntoSumTree(root->left) + convertIntoSumTree(root->right);
            return root->val;
        }
        if(root->left){
            root->val+=convertIntoSumTree(root->left);
            return root->val;
        }
        root->val+=convertIntoSumTree(root->right);
        return root->val;
    }
    void preOrderTraversal(TreeNode* root){
        if(!root){ return;}
        mp[root->val]++;
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> output;
        int mx=0;
        convertIntoSumTree(root);
        preOrderTraversal(root);
        cout<<endl;
        for(auto elem:mp){
            mx=max(elem.second,mx);
        }
        for(auto elem:mp){
            if(elem.second == mx){
                output.push_back(elem.first);
            }
        }
        mp.clear();
        return output;
    }
};