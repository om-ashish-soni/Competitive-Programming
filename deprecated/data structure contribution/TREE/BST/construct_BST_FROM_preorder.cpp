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
    TreeNode* buildtree(int preorder[],int inorder[],int n,int &i){
        if(n<=0 ) return NULL;
        TreeNode* root=new TreeNode(*preorder);
        int *curr=find(inorder,inorder+n,*preorder);
        int temp=i;
        i++;
        root->left=buildtree(preorder+1,inorder,curr-inorder,i);
        curr++;
        root->right=buildtree(preorder+i-temp,curr,inorder+n-curr,i);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n=preorder.size(),i=0;
        int pre[n],in[n];
        for(int i=0;i<n;i++) pre[i]=preorder[i];
        sort(preorder.begin(),preorder.end());
        for(int i=0;i<n;i++) in[i]=preorder[i];
        return buildtree(pre,in,n,i);
    }
};