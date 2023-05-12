// Problem Link : https://leetcode.com/problems/search-a-2d-matrix-ii/
// Problem type : divide and conquer
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        int i=0,j=n-1;
        while(i<m && j>=0){
            if(matrix[i][j]==target) return true;
            if(matrix[i][j]<target) i++;
            else j--;
        }
        return false;
    }
};
