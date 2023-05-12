// problem link : https://leetcode.com/problems/binary-tree-maximum-path-sum/
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
    map<TreeNode*,vector<int>> mp;
    int dopathsum(TreeNode* root){
        if(!root) return INT_MIN;
        int mx=INT_MIN;
        mx=max(mx,dopathsum(root->left));
        mx=max(mx,dopathsum(root->right));
        int curr=root->val;
        
        vector<int> row={curr,curr,curr};
        vector<int> &left=mp[root->left];
        vector<int> &right=mp[root->right];
        row[0]=max(row[0],curr+max(left[0],right[0]));
        row[2]=max(row[2],curr+max(left[2],right[2]));
        row[1]=max(row[1],left[0]+right[0]+curr);
        row[1]=max(row[1],left[0]+right[2]+curr);
        row[1]=max(row[1],left[2]+right[0]+curr);
        row[1]=max(row[1],left[2]+right[2]+curr);
        // cout<<row[0]<<" , "<<row[1]<<" , "<<row[2]<<endl;
        mx=max(mx,max(row[0],max(row[1],row[2])));
        mp[root]=row;
        return mx;
    }
    int maxPathSum(TreeNode* root) {
        mp.clear();
        mp[NULL]={0,0,0};
        int mx=dopathsum(root);
        return mx;
    }
};
