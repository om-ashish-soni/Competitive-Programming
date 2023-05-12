// problem link : https://leetcode.com/problems/contains-duplicate/
// solution : below code


class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        map<int,int> hash;
        for(auto num:nums) hash[num]++;
        for(auto pr:hash) if(pr.second>1) return true;
        return false;
    }
};
