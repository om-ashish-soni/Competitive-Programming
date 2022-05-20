// problem link : https://leetcode.com/problems/unique-paths-ii/
// solution : below code

#define vi vector<int>
#define vvi vector<vi>
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size();
        int n=obstacleGrid.front().size();
        vvi & grid=obstacleGrid;
        vvi dp(m+1,vi(n+1,0));
        dp[0][0]=1;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==0){
                    dp[i+1][j]+=dp[i][j];
                    dp[i][j+1]+=dp[i][j];
                }
            }
        }
        if(grid[m-1][n-1]==0) return dp[m-1][n-1];
        return 0;
    }
};
