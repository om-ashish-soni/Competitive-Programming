// problem link : https://leetcode.com/problems/removing-minimum-and-maximum-from-array/description/
// solution : below code

class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int mn_index=min_element(nums.begin(),nums.end())-nums.begin();
        int mx_index=max_element(nums.begin(),nums.end())-nums.begin();
        int first=min(mn_index,mx_index);
        int second=max(mn_index,mx_index);
        int n=nums.size();
        if(first==second){
            return min(first+1,n-first);
        }
        int left=second+1;
        int right=n-first;
        int mid=first+1+(n-second);
        return min(left,min(right,mid));
    }
};