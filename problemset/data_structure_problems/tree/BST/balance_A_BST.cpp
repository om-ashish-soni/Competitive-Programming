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
    TreeNode* constructBST(int arr[],int n){
        if(n<=0) return NULL;
        int mid=arr[n/2];
        TreeNode* root=new TreeNode(mid);
        root->left=constructBST(arr,n/2);
        root->right=constructBST(arr+n/2+1,n-n/2-1);
        return root;
    }
    void gatherNode(TreeNode* root,vector<int> &v){
        if(!root) return;
        gatherNode(root->left,v);
        v.push_back(root->val);
        gatherNode(root->right,v);
    }
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> v;
        gatherNode(root,v);
        int n=v.size();
        int arr[n];
        for(int i=0;i<n;i++) arr[i]=v[i];
        return constructBST(arr,n);
    }
};