// Problem link : https://leetcode.com/problems/search-a-2d-matrix/
//Problem type: divide and conquer

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m=matrix.size(),n=matrix[0].size();
        int l,r,mid;
        l=0,r=m-1;
        mid=(r-l)/2;
        while(l<r){
            if(r-l < 2) break;
            mid=l+(r-l)/2;
            if(target == matrix[mid][0]) return true;
            if(target>matrix[mid][0]){
                l=mid;
            }else{
                r=mid;
            }
        }
        if(l!=r) return binary_search(matrix[l].begin(),matrix[l].end(),target) || binary_search(matrix[r].begin(),matrix[r].end(),target);
        return binary_search(matrix[l].begin(),matrix[l].end(),target);
    }
};
