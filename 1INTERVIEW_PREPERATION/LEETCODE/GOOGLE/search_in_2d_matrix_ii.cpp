// problem link : https://leetcode.com/problems/search-a-2d-matrix-ii/
// solution : below code
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rowlimit=lower_bound(matrix[0].begin(),matrix[0].end(),target)-matrix[0].begin();
        if(rowlimit==matrix[0].size()) rowlimit--;
        for(int i=0;i<=rowlimit;i++){
            int l=0,r=matrix.size();
            while(l<r){
                int mid=(l+r)/2;
                auto found=matrix[mid][i];
                if(found==target) return true;
                else if(found<target) l=mid+1;
                else r=mid;
            }
        }
        return false;
    }
};
