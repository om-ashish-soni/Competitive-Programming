// Problem link : https://leetcode.com/problems/score-after-flipping-matrix/
// Problem type : Greedy 
class Solution {
public:
    void flip(vector<int> &v){
        for(int i=0;i<v.size();i++){
            if(v[i]==0) v[i]=1;
            else v[i]=0;
        }
    }
    int matrixScore(vector<vector<int>>& grid) {
        int m,n;
        m=grid.size();
        n=grid[0].size();
        for(auto &v:grid){
            if(v[0]==0){
                flip(v);
            }
        }
        vector<int> colSum(n,0);
        for(int j=0;j<n;j++){
            for(int i=0;i<m;i++){
                colSum[j]+=grid[i][j];
            }
        }
        int mul=1;
        int ans=0;
        for(int i=n-1;i>=0;i--,mul*=2){
            int colTotal=colSum[i];
            colTotal=max(colTotal,m-colTotal);
            ans+=colTotal*mul;
        }
        return ans;
    }
};
