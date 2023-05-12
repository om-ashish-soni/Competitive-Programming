// problem link : https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
// solution : below code

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> dups;
        map<int,int> mp;
        for(auto num:nums){
            mp[num]++;
        }
        for(auto &pr:mp){
            if(pr.second>1) dups.push_back(pr.first);
        }
        return dups;
    }
};
