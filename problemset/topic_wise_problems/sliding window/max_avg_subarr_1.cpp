// problem link : https://leetcode.com/problems/maximum-average-subarray-i/description/
// solution : below code
class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        
        vector<int> pref=nums;
        long long mx=LLONG_MIN;
        if(k==1) mx=nums.front();
        for(int i=1;i<nums.size();i++){
            pref[i]+=pref[i-1];
            if(i>=k-1){
                long long delta=pref[i]-pref[i-k+1]+nums[i-k+1];
                mx=max(mx,delta);
            }
        }
        double mean=(mx*1.0)/k;
        return mean;
    }
};