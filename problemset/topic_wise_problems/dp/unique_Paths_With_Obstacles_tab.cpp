class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size();
        int n=obstacleGrid[0].size();
        int arr[m][n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++) arr[i][j]=0;
        }arr[0][0]=1;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(obstacleGrid[i][j] == 0){if(j+1<n) arr[i][j+1]+=arr[i][j];
                if(i+1<m) arr[i+1][j]+=arr[i][j];}
            }
        }
        if(obstacleGrid[m-1][n-1]==0) return arr[m-1][n-1];
        return 0;
    }
};