//Problem link: https://leetcode.com/problems/search-in-rotated-sorted-array/
// Problem type: Binary Search
class Solution {
public:
    int searchSlave(vector<int>& nums,int target,int start,int end){
        //base case for element not found...
        if(start>=end) return -1;
        //finding center (pivot or middle)
        int center=start+(end-start)/2;
        //actual comparison
        if(nums[center]==target){ 
            return center;
        }
        else if(target<nums[center]){
            if(target<nums[start] ) {
                if(nums[start]>=nums[center]){ 
                    return searchSlave(nums,target,start,center);
                }else{
                    return searchSlave(nums,target,center+1,end);
                }
            }
            else{
                return searchSlave(nums,target,start,center);
            }
        }else{
            if(target>nums[end-1] ){  
                if(nums[center]<=nums[end-1]){ 
                    return searchSlave(nums,target,start,center);
                }else{
                    return searchSlave(nums,target,center+1,end);
                }
            }else{
                return searchSlave(nums,target,center+1,end);
            }
        }
        //not any case , for error handling(#non void function does not return any value)
        return -1;       
    }
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        return searchSlave(nums,target,0,n);
    }
};
