// problem link : https://leetcode.com/problems/path-sum-ii/
// solution : below code

class Solution {
public:
    bool getpaths(TreeNode* root,map<TreeNode*,vi>& mp,vvi & v,int target){
        if(!root){
            return false;
        }
        if(!root->left && !root->right){
            if(target==root->val){
                int sz=v.size();
                v.pb({root->val});
                mp[root].pb(sz);
                return true;
            }
            return false;
        }
        
        bool left=getpaths(root->left,mp,v,target-root->val);
        bool right=getpaths(root->right,mp,v,target-root->val);
        // cout<<"root : "<<root->val<<endl;
        vi & myrow=mp[root];
        vi & leftrow=mp[root->left];
        FEACH(index,leftrow){
            v[index].pb(root->val);
            myrow.pb(index);
        }
        vi & rightrow=mp[root->right];
        FEACH(index,rightrow){
            v[index].pb(root->val);
            myrow.pb(index);
        }
        
        return left || right;
    }
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vvi v;
        if(!root) return v;
        map<TreeNode*,vi> mp;
        getpaths(root,mp,v,targetSum);
        FEACH(row,v){
            REVERSE(row);
        }
        return v;
    }
};
