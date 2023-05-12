// problem link : https://leetcode.com/problems/minimum-falling-path-sum/
// solution : below code
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n==1) return matrix[0][0];
        // vector<vector<int>> vmat=matrix;
        for(int i=1;i<n;i++){
            matrix[i][0]+=min(matrix[i-1][0],matrix[i-1][1]);
            matrix[i][n-1]+=min(matrix[i-1][n-1],matrix[i-1][n-2]);
            for(int j=1;j<n-1;j++){
                matrix[i][j]+=min(matrix[i-1][j],min(matrix[i-1][j-1],matrix[i-1][j+1]));
            }
        }
        return *min_element(matrix[n-1].begin(),matrix[n-1].end());
    }
};
