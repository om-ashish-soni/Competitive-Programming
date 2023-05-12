// Problem link : https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/submissions/
// Problem type : Greedy
class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        int m,n;
        m=rowSum.size();
        n=colSum.size();
        vector<int> row(n);
        vector<vector<int>> grid(m,row);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int elem=min(rowSum[i],colSum[j]);
                rowSum[i]-=elem;
                colSum[j]-=elem;
                grid[i][j]=elem;
            }
        }
        return grid;
    }
};
