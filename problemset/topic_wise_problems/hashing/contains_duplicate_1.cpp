// problem link : https://leetcode.com/problems/contains-duplicate/description/
// solution : below code

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int,bool> hashmap;
        for(auto num:nums){
            if(hashmap.count(num)) return true;
            hashmap[num]=true;
        }
        return false;
    }
};