// problem link : https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/
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
#define pii pair<int,int>
class Solution {
public:
    pair<int,int> averageOfSubtree(TreeNode* root,int &ctr) {
        if(root==NULL) return {0,0};
        pii intake,lefttake,righttake;
        intake={root->val,1};
        lefttake=averageOfSubtree(root->left,ctr);
        righttake=averageOfSubtree(root->right,ctr);
        intake.first+=lefttake.first+righttake.first;
        intake.second+=lefttake.second+righttake.second;
        if(root->val == intake.first/intake.second){
            ctr++;
        }
        return intake;
    }
    int averageOfSubtree(TreeNode* root) {
        int ctr=0;
        averageOfSubtree(root,ctr);
        return ctr;
    }
};
