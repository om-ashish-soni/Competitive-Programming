// problem link : https://leetcode.com/problems/next-permutation/
// solution : below code

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int swapped=0;
        int n=nums.size();
        
        for(int i=n-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                swapped=1;
                sort(begin(nums)+i+1,end(nums));
                int index=upper_bound(begin(nums)+i+1,end(nums),nums[i])-begin(nums);
                swap(nums[i],nums[index]);
                sort(begin(nums)+i+1,end(nums));
                return;
            }
        }
        if(swapped==0) reverse(begin(nums),end(nums));
    }
};
