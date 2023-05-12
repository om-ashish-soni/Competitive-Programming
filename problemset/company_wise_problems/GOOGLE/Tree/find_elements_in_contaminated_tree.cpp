// problem link : https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/
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
class FindElements {
public:
    unordered_map<int,bool> isPresent;
    void build(TreeNode* root,int val){
        if(!root) return;
        isPresent[val]=true;
        root->val=0;
        build(root->left,2*val+1);        
        build(root->right,2*val+2);

    }
    FindElements(TreeNode* root) {
        
        build(root,0);
    }
    
    bool find(int target) {
        return isPresent.count(target)>0;        
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
