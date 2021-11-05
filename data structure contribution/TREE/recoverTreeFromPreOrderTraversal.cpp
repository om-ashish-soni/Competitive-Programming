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
    TreeNode* recoverFromPreorder(string& traversal,int level,int &start) {
        if(traversal.size()==0) return NULL;
        int i=start;
        while(traversal[i] == '-'){
            i++;
        }
        if(i-start != level) return NULL;
        string number="";
        while(i<traversal.size() && traversal[i] != '-'){
            number+=traversal[i];
            i++;
        }
        TreeNode* root=new TreeNode(stoi(number));
        start=i;
        root->left=recoverFromPreorder(traversal,1+level,start);
        root->right=recoverFromPreorder(traversal,1+level,start);
        return root;
    }
    TreeNode* recoverFromPreorder(string traversal){
        int level=0,start=0;
        return recoverFromPreorder(traversal,level,start);
    }
};