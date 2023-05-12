// problem link : https://leetcode.com/problems/k-radius-subarray-averages/description/
// solution : below code

class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        vector<long long> pref;
        for(auto num:nums) pref.push_back(num);
        int n=nums.size();
        for(int i=1;i<n;i++){
            pref[i]+=pref[i-1];
        }
        vector<int> avg(n,-1);
        for(int i=0;i<n;i++){
            if(i-k>=0 && i+k<n){
                long long left,right;
                left=pref[i]-pref[i-k]+nums[i-k];
                right=pref[i+k]-pref[i];
                avg[i]=(left+right)/(2*k+1);
            }
        }
        return avg;
    }
};