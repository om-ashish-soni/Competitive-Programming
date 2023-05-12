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
    TreeNode* constructMaximumBinaryTree(int arr[],int n) {
        if(n==0) return NULL;
        auto maxElemPtr=max_element(arr,arr+n);
        TreeNode* root=new TreeNode(*maxElemPtr);
        root->left=constructMaximumBinaryTree(arr,maxElemPtr-arr);
        root->right=constructMaximumBinaryTree(maxElemPtr+1,n-(maxElemPtr-arr)-1);
        return root;
    }
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        // first approach using array
        int arr[nums.size()];
        for(int i=0;i<nums.size();i++) arr[i]=nums[i];
        return constructMaximumBinaryTree(arr,nums.size());
        // second approach using vector
        if(nums.size()==0) return NULL;
        vector<int> left,right;
        auto maxElemIt=max_element(nums.begin(),nums.end());
        for(auto it=nums.begin();it!=maxElemIt;++it) left.push_back(*it);
        for(auto it=maxElemIt+1;it!=nums.end();++it) right.push_back(*it);
        TreeNode* root=new TreeNode(*maxElemIt);
        root->left=constructMaximumBinaryTree(left);
        root->right=constructMaximumBinaryTree(right);
        return root;
    }
};