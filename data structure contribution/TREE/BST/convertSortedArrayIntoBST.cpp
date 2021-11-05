/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     Thttps://assets.leetcode.com/uploads/2021/02/18/btree2.jpgreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void preOrder(TreeNode * root){
        if(!root) return;
        cout<<root->val<<" ";
        preOrder(root->left);
        preOrder(root->right);
        
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int n=nums.size();
        if(n==0){
            return NULL;
        }
        if(n==1){
            TreeNode* root=new TreeNode;
            root->val=nums[0];
            root->left=NULL;
            root->right=NULL;
            return root;
        }
        TreeNode* root=new TreeNode;
        root->val=nums[n/2];
        vector<int> leftV,rightV;
        for(int i=0;i<n/2;i++){
            leftV.push_back(nums[i]);
        }
        for(int i=n/2+1;i<n;i++){
            rightV.push_back(nums[i]);
        }
        if(leftV.size()) root->left=sortedArrayToBST(leftV);
        else root->left=NULL;
        if(rightV.size()) root->right=sortedArrayToBST(rightV);
        else root->right=NULL;
        
        return root;
    }
    
};