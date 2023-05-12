// problem link : https://leetcode.com/problems/count-square-submatrices-with-all-ones/
// solution : below code

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix.front().size();
        vector<vector<int>> rstreak(m,vector<int>(n,0));
        vector<vector<int>> dstreak(m,vector<int>(n,0));
        vector<vector<int>> streak(m,vector<int>(n,0));
        for(int i=0;i<m;i++){
            rstreak[i][n-1]=matrix[i][n-1];
            for(int j=n-2;j>=0;j--){
                if(matrix[i][j]!=0) rstreak[i][j]=matrix[i][j]+rstreak[i][j+1];
            }
        }
        
        for(int j=0;j<n;j++){
            dstreak[m-1][j]=matrix[m-1][j];
            for(int i=m-2;i>=0;i--){
                if(matrix[i][j]!=0) dstreak[i][j]=matrix[i][j]+dstreak[i+1][j];
            }
        }
        int sm=0;
        for(int j=n-1;j>=0;j--){
            streak[m-1][j]=matrix[m-1][j];
            sm+=streak[m-1][j];
        }
        for(int i=m-2;i>=0;i--){
            streak[i][n-1]=matrix[i][n-1];
            sm+=streak[i][n-1];
            for(int j=n-2;j>=0;j--){
                if(matrix[i][j]==0) continue;
                int currStreak=min(min(rstreak[i][j],dstreak[i][j]),1+streak[i+1][j+1]);     
                streak[i][j]=currStreak;
                sm+=currStreak;
            }
        }
        return sm;
    }
};
