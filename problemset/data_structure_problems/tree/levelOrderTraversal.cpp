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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> nodes,leftChilds,rightChilds;
        vector<int> nodesAtLevel;
        if(!root) return nodes;
        if(!root->left && !root->right){
            nodesAtLevel.push_back(root->val);
            nodes.push_back(nodesAtLevel);
            return nodes;
        }
        leftChilds=levelOrder(root->left);
        rightChilds=levelOrder(root->right);
        int leftlen=leftChilds.size();
        int rightlen=rightChilds.size();
        int minlen=min(leftlen,rightlen);
        int i=0;
        nodesAtLevel.push_back(root->val);
        nodes.push_back(nodesAtLevel);
        
        for(i=0;i<minlen;i++){
            vector<int> temp;
            temp.insert(temp.begin(),leftChilds[i].begin(),leftChilds[i].end());
            temp.insert(temp.end(),rightChilds[i].begin(),rightChilds[i].end());
            
            nodes.push_back(temp);
        }
        if(i<leftlen){
            for(;i<leftlen;i++){
                nodes.push_back(leftChilds[i]);
            }
        }
        if(i<rightlen){
            for(;i<rightlen;i++){
                nodes.push_back(rightChilds[i]);
            }
        }
        return nodes;
    }
};