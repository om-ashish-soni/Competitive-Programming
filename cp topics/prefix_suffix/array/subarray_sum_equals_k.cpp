// problem link : https://leetcode.com/problems/subarray-sum-equals-k/
// solution : below code

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n=nums.size();
        int ctr=0;
        unordered_map<int,int> hash;
        hash[0]=1;
        int sm=0;
        for(int i=0;i<n;i++){
            sm+=nums[i];
            int rem=sm-k;
            if(hash.count(rem)){
                ctr+=hash[rem];
            }
            hash[sm]++;
        }
        return ctr;
    }
};
