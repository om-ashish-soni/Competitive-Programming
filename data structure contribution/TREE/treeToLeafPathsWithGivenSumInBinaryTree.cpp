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
    vector<vector<int>> binaryTreePaths(TreeNode* root) {
        vector<vector<int>> paths;
        vector<int> thispath;
        if(!root) return paths;
        if(!root->left && !root->right){
            thispath.push_back(root->val);
            paths.push_back(thispath);
            return paths;
        }
        
        vector<vector<int>> subpathsleft,subpathsright;
        subpathsleft=binaryTreePaths(root->left);
        subpathsright=binaryTreePaths(root->right);
        for(int i=0;i<subpathsleft.size();i++){
            subpathsleft[i].push_back(root->val);
            paths.push_back(subpathsleft[i]);
        }
        for(int i=0;i<subpathsright.size();i++){
            subpathsright[i].push_back(root->val);
            paths.push_back(subpathsright[i]);
        }
        return paths;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> paths=binaryTreePaths(root);
        vector<vector<int>> output;
        for(int i=0;i<paths.size();i++){
            int sum=0;
            sum=accumulate(paths[i].begin(),paths[i].end(),sum);
            if(sum==targetSum){
                reverse(paths[i].begin(),paths[i].end());
                output.push_back(paths[i]);
            }
        }
        return output;
    }
};