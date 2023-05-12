// problem link : https://leetcode.com/problems/maximum-subarray/
// solution : below code

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int mx_sum=-1;
        int sum_upto=-1;
        int mx=*max_element(nums.begin(),nums.end());
        for(auto num:nums){
            sum_upto=max(num+sum_upto,num);
            mx_sum=max(mx_sum,sum_upto);
        }
        if(mx<0) return mx;
        return mx_sum;
    }
};
