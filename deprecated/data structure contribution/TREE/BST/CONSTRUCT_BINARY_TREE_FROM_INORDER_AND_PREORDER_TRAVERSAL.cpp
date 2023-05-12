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
    void inorderTra(TreeNode* root){
        if(!root) return;
        inorderTra(root->left);
        cout<<root->val;
        inorderTra(root->right);
    }
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n=preorder.size();
        int pre[n],in[n];
        for(int i=0;i<n;i++){
            pre[i]=preorder[i];
            in[i]=inorder[i];
        }
        int i=0;
        TreeNode* root= buildtree(pre,in,n,i);
        return root;
    }
};