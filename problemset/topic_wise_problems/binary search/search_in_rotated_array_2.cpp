// problem link : https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/
// solution : below code

class Solution {
public:
    int get_pivot(vector<int>& nums,int l,int r){
        if(l+1<=r){
            if(nums[l]>nums[l+1]) return l+1;
        }
        if(l+1>=r) return 0;
        int mid=(l+r)/2;
        if(nums[l]>nums[mid]) return get_pivot(nums,l,mid);
        if(nums[mid]>nums[r]) return get_pivot(nums,mid,r);
        int first=get_pivot(nums,l,mid);
        if(first != 0) return first;
        return get_pivot(nums,mid,r);
    }

    bool search(vector<int>& nums, int target) {
        int pivot=0;
        int n=nums.size();
        int l=0;
        int r=n-1;
        pivot=get_pivot(nums,l,r);
        bool first=binary_search(nums.begin(),nums.begin()+pivot,target);
        if(first) return true;
        return binary_search(nums.begin()+pivot,nums.end(),target);
    }
};