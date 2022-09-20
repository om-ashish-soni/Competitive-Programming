// problem link : https://leetcode.com/problems/continuous-subarray-sum/
// solution : below code

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n=nums.size();
        unordered_map<int,int> hash;
        int sm=0;
        hash[0]++;
        sm+=nums[0];
        hash[sm%k]++;
        for(int i=1;i<n;i++){
            sm+=nums[i];
            int limit=0;
            int mod=sm%k ;
            if(mod == (sm-nums[i])%k) limit++;
            if(hash.count(mod) && hash[mod]>limit){
                return true;
            }            
            hash[mod]++;
        }
        return false;
    }
};
