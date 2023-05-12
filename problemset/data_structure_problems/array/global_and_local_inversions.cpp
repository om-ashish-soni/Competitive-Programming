// problem link : https://leetcode.com/problems/global-and-local-inversions/
// solution : below code

class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n-1;i++){
            if(nums[i]>nums[i+1]){
                swap(nums[i],nums[i+1]);
                i++;
            }
        }
        
        for(int i=0;i<n-1;i++){
            if(nums[i]>nums[i+1]) return false;
        }
        return true;
    }
};
