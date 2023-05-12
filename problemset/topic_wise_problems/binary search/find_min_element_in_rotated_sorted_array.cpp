// problem link : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
// solution : below code

class Solution {
public:
    int findMin(vector<int>& nums) {
        int index=0;
        int l=0;
        int r=nums.size()-1;
        while(l<=r){
            bool flag=(l==r);
            int mid=(l+r)/2;
            if(nums[l]<nums[index]){
                index=l;
            }
            if(nums[l]>nums[mid]){
                r=mid;
            }
            else if(nums[mid]>nums[r]){
                l=mid+1;
            }
            else{
                break;
            }
            if(flag) break;
        }
        return nums[index];
    }
}; 