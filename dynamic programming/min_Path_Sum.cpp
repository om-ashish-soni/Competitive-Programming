//tabulation

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<int> elemV (grid[0].size(),INT_MAX);
        vector<vector<int>> v(grid.size(),elemV);
        v[0][0]=grid[0][0];
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[i].size();j++){
                if(i+1 < grid.size()) v[i+1][j]=min(v[i+1][j],grid[i+1][j]+v[i][j]);
                if(j+1<grid[i].size()) v[i][j+1]=min(v[i][j+1],grid[i][j+1]+v[i][j]);
            }
        }
        return v[grid.size()-1][grid[0].size()-1];
    }
};

//memoization

class Solution {
public:
    int minPathSum(vector<vector<int>> &grid,vector<vector<int>> &v,int i=0,int j=0){
        if(v[i][j] != INT_MAX) return v[i][j];
        if(i < grid.size()-1 ) v[i][j]=min(v[i][j],minPathSum(grid,v,i+1,j));
        if(j < grid[0].size()-1) v[i][j]=min(v[i][j],minPathSum(grid,v,i,j+1));
        if(v[i][j]!=INT_MAX) v[i][j]+=grid[i][j];
        else v[i][j]=grid[i][j];
        return v[i][j];
    }
    int minPathSum(vector<vector<int>>& grid) {
        vector<int> v(grid[0].size(),INT_MAX);
        vector<vector<int>> memo(grid.size(),v);
        return minPathSum(grid,memo);
        return 0;
    }
};