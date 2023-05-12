// problem link : https://leetcode.com/problems/search-in-rotated-sorted-array/
// solution : below code

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        int left=0,right=nums.size()-1;
        while(left<right && left<n && right>=0){
            
            int mid=(left+right)/2;
            if(target==nums[mid]) return mid;
            if(nums[left]<=nums[right]){
                if(target<nums[left]) return -1;
                if(target>nums[right]) return -1;
                if(target<nums[mid]){
                    right=mid-1;
                }else{
                    left=mid+1;
                }
            }else{
                if(target<nums[mid]){
                    if(nums[left]<=nums[mid]){
                        if(target>=nums[left]) right=mid-1;
                        else left=mid+1;
                    }else{
                        right=mid-1;
                    }
                }else{
                    if(nums[mid]<=nums[right]){
                        if(target<=nums[right]){
                            left=mid+1;
                        }else{
                            right=mid-1;
                        }
                    }else{
                        left=mid+1;
                    }
                }
            }
            
        }
        if(left<n && target==nums[left]) return left;
        if(right>=0 && target==nums[right]) return right;
        return -1;
    }
};
