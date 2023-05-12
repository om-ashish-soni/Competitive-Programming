// problem link : https://leetcode.com/problems/maximal-square/description/
// solution : below code

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int n=matrix.size();
        int m=matrix.front().size();
        vector<vector<int>> dp(n,vector<int>(m,0));
        int maxSquare=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(matrix[i][j]=='1'){
                    int mx=0;
                    if(i-1>=0 && j-1>=0){
                        mx=min(dp[i-1][j],min(dp[i-1][j-1],dp[i][j-1]));
                    }
                    dp[i][j]=1+mx;
                    maxSquare=max(maxSquare,dp[i][j]);
                }
            }
        }
        return maxSquare*maxSquare;
    }
};