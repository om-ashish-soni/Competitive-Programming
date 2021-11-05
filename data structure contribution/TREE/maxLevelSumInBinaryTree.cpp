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
    
    void maxLevelSum(TreeNode* root,vector<int> &sum,int level=0){
        if(!root) return;
        if(sum.size()>level){
            sum[level]+=root->val;
        }else{
            sum.push_back(root->val);
        }
        maxLevelSum(root->left,sum,1+level);
        maxLevelSum(root->right,sum,1+level);
        return;
    }
    int maxLevelSum(TreeNode* root) {
        vector<int> sum;
        maxLevelSum(root,sum);
        return 1+(max_element(sum.begin(),sum.end())-sum.begin());
    }
};