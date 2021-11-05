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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> paths;
        if(!root) return paths;
        if(!root->left && !root->right){
            ostringstream leaf;
            leaf<<root->val;
            paths.push_back(leaf.str());
            return paths;
        }
        ostringstream current;
        current<<root->val;
        string curr=current.str();
        curr+="->";
        vector<string> subpathsleft,subpathsright;
        subpathsleft=binaryTreePaths(root->left);
        subpathsright=binaryTreePaths(root->right);
        for(int i=0;i<subpathsleft.size();i++){
            paths.push_back(curr+subpathsleft[i]);
        }
        for(int i=0;i<subpathsright.size();i++){
            paths.push_back(curr+subpathsright[i]);
        }
        return paths;
    }
};