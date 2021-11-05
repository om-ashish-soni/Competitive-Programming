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
    int heightOfTree(TreeNode* root){
        if(!root) return 0;
        return 1+max(heightOfTree(root->left),heightOfTree(root->right));
    }
    void deepestLeavesSum(TreeNode* root,int height,int level,int* sum){
        if(!root) return;
        // cout<<level<<" "<<height<<endl;
        if(1+level == height){
            *sum += root->val;
            return;
        }
        deepestLeavesSum(root->left,height,1+level,sum);
        deepestLeavesSum(root->right,height,1+level,sum);
        return;
    }
    int deepestLeavesSum(TreeNode* root) {
        int height=heightOfTree(root);
        int sum=0;
        deepestLeavesSum(root,height,0,&sum);
        return sum;
    }
};