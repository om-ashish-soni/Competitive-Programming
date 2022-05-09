// problem link : https://leetcode.com/contest/weekly-contest-292/problems/check-if-there-is-a-valid-parentheses-string-path/
// solution : below code

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int n=grid.size();
        vector<vector<int>> mat(n);
        int m=grid[0].size();
        int limit=210;
        vector<bool> vals(limit,false);
        vector<vector<vector<bool>>> dp(n,*new vector<vector<bool>>);
        for(int i=0;i<n;i++){
            mat[i].resize(m);
            dp[i].resize(m);
            for(int j=0;j<m;j++){
                dp[i][j]=vals;
                if(grid[i][j]=='('){
                    mat[i][j]=1;
                }
                else mat[i][j]=-1;
            }
        }
        if(mat[0][0]>0) dp[0][0][mat[0][0]]=true;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                for(int k=0;k<limit;k++){
                    if(dp[i][j][k]==true){
                        if(i+1<n and k+mat[i+1][j]>=0 and k+mat[i+1][j]<limit){
                            dp[i+1][j][k+mat[i+1][j]]=true;
                        }
                        if(j+1<m and k+mat[i][j+1]>=0 and k+mat[i][j+1]<limit){
                            dp[i][j+1][k+mat[i][j+1]]=true;
                        }
                    }
                }
            }
        }
        cout<<std::boolalpha<<dp[n-1][m-1][0]<<endl;
        return dp[n-1][m-1][0];
        
    }
};
