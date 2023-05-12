# N Queens 
// Problem link : https://leetcode.com/problems/n-queens/
// Solution : below code

class Solution {
public:
    void nQueen(int n,vector<int>&recStack,vector<vector<int>>& v,int index,int& depth){
        if(index>=n){
            if(depth<index){
                depth=index;
                v.clear();
            }
            v.push_back(recStack);
            return;
        }
        int calls=0;
        vector<bool> space(n,true);
        for(int i=0;i<index;i++){
            int diff=index-i;
            space[recStack[i]]=false;
            if(recStack[i]+diff<n) space[recStack[i]+diff]=false;
            if(recStack[i]-diff>=0) space[recStack[i]-diff]=false;
        }
        // for(auto sp:space) cout<<sp<<" ";cout<<endl;
        for(int i=0;i<n;i++){
            if(space[i]){
                calls++;
                recStack[index]=i;
                nQueen(n,recStack,v,index+1,depth);
            }
        }
        recStack[index]=-1;
        // cout<<"index : "<<index<<endl;
        if(depth>index) return;
        if(calls==0){
            if(depth<index){
                depth=index;
                v.clear();
            }
            v.push_back(recStack);
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> v;
        vector<int> recStack(n,-1);
        int depth=0;
        for(int i=0;i<n;i++){
            recStack[0]=i;
            nQueen(n,recStack,v,1,depth);
        }
        if(depth<n){
            return *new vector<vector<string>>;
        }
        string s;
        for(int i=0;i<n;i++) s+='.';
        vector<string> row(n,s);
        vector<vector<string>> soln(v.size(),row);
        for(int i=0;i<v.size();i++){
            for(int j=0;j<v[i].size();j++){
                if(v[i][j]!=-1){
                    soln[i][j][v[i][j]]='Q';
                }
            }
        }
        return soln;
    }
};
