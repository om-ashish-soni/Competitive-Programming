// problem link : https://leetcode.com/problems/maximum-sum-circular-subarray/description/
// solution : below code

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n=nums.size();
        int sm=0;
        vector<int> dp_suff(n,0);
        dp_suff[n-1]=nums[n-1];
        for(int i=n-2;i>=0;i--){
            dp_suff[i]=dp_suff[i+1]+nums[i];
        }
        dp_suff[n-1]=max(dp_suff[n-1],0);
        for(int i=n-2;i>=0;i--){
            dp_suff[i]=max(dp_suff[i],dp_suff[i+1]);
        }
        int final_mx=INT_MIN;
        int mx_so_far=0;
        int pref_sm=0;
        for(int i=0;i<n;i++){
            pref_sm+=nums[i];
            mx_so_far=max(mx_so_far,0);
            mx_so_far+=nums[i];
            int mx_suff=(i+1<n)?dp_suff[i+1]:0;
            int curr_mx=pref_sm+mx_suff;
            final_mx=max(final_mx,curr_mx);
            final_mx=max(final_mx,mx_so_far);
        }
        return final_mx;
    }
};