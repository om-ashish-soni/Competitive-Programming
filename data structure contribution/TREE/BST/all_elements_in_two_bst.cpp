// problem link : https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
// solution : below code

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
    void dfs(TreeNode* root,stack<int> &s){
        if(!root) return;
        dfs(root->right,s);
        s.push(root->val);
        dfs(root->left,s);
    }
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        stack<int> s1,s2;
        vector<int> v;
        dfs(root1,s1);
        dfs(root2,s2);
        while(s1.size() && s2.size()){
            if(s1.top()<s2.top()){
                v.push_back(s1.top());
                s1.pop();
            }else{
                v.push_back(s2.top());
                s2.pop();
            }
        }
        while(s1.size()){
            v.push_back(s1.top());
            s1.pop();
        }
        while(s2.size()){
            v.push_back(s2.top());
            s2.pop();
        }
        return v;
    }
};
