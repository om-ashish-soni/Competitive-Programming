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
    static bool comp(pair<int,int> &p1,pair<int,int> &p2){
        if(p1.second==p2.second){
            return p1.first<p2.first;
        }
        return p1.second<p2.second;
    }
    int levelOf(TreeNode* root){
        if(!root) return 0;
        int level=0;
        level=max(level,1+levelOf(root->left));
        level=max(level,1+levelOf(root->right));
        return level;
    }
    void verticalTraversal(TreeNode* root,vector<vector<pair<int,int>>> &v,int &n,int i=0,int level=0){
        if(!root) {return;}
        v[n+i].push_back({root->val,level});
        verticalTraversal(root->right,v,n,i+1,level+1);
        verticalTraversal(root->left,v,n,i-1,level+1);
        return ;
    }
    vector<vector<int>> verticalTraversal(TreeNode* root){
        int n=levelOf(root);
        n=pow(2,n-1)+1;
        vector<vector<pair<int,int>>> v(n);
        n/=2;
        verticalTraversal(root,v,n);
        vector<vector<int>> output;
        for(int i=0;i<v.size();i++){
            if(v[i].size()){ 
                sort(v[i].begin(),v[i].end(),comp);
                vector<int> temp;
                for(auto it=v[i].begin();it!=v[i].end();++it) temp.push_back(it->first);
                output.push_back(temp);
            }
                
        }
        return output;
    }
};