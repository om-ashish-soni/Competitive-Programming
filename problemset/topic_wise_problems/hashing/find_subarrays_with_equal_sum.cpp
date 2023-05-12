// problem link : https://leetcode.com/problems/find-subarrays-with-equal-sum/description/
// solution : below code

class Solution {
public:
    bool findSubarrays(vector<int>& nums) {
        #define map unordered_map
        map<int,int> mp;
        int n=nums.size();
        for(int i=0;i<n-1;i++){
            int sm=nums[i]+nums[i+1];
            if(mp.count(sm)) return true;
            mp[sm]++;
        }
        return false;
    }
};