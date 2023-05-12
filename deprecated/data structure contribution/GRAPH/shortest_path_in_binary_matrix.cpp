// problem link : https://leetcode.com/problems/shortest-path-in-binary-matrix/
// solution : below code

#define pipii pair<int,pair<int,int>>
class Solution {
public:
    inline bool isValid(int i,int j,int n){
        return i>=0 and i<n and j>=0 and j<n;
    }
    int spath(vector<vector<int>>& grid,int i,int j){
        int n=grid.size();
        int dp[n][n];
        int MAX=1e9 + 7;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) dp[i][j]=MAX;
        priority_queue<pipii,vector<pipii>,greater<pipii>> pq;

        if(grid[0][0]==0){
            pq.push({1,{0,0}});
            dp[0][0]=1;
        }
        while(pq.size()>0){
            pipii top=pq.top();pq.pop();
            int v_d,vi,vj;
            v_d=top.first;
            vi=top.second.first;
            vj=top.second.second;
            // cout<<vi<<" , "<<vj<<" : "<<v_d<<endl;
            if(dp[vi][vj] != v_d) continue;
            for(int row=-1;row<=1;row++){
                for(int col=-1;col<=1;col++){
                    int ci=row+vi;
                    int cj=col+vj;
                    if((ci>=0 and ci<n and cj>=0 and cj<n) and grid[ci][cj]==0){
                        if(dp[ci][cj]>v_d+1){
                            dp[ci][cj]=v_d+1;
                            pq.push({dp[ci][cj],{ci,cj}});
                        }
                    }
                }
            }
        }
        if(dp[n-1][n-1] != MAX) return dp[n-1][n-1];
        return -1;
    }
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        return spath(grid,0,0);
    }
};
