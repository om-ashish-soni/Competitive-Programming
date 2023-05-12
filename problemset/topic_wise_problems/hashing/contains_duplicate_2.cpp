// problem link : https://leetcode.com/problems/contains-duplicate-ii/description/
// solution : below code

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int,int> hashmap;
        for(int i=0;i<nums.size();i++){
            if(hashmap.count(nums[i])){
                int last=hashmap[nums[i]];
                int diff=i-last;
                if(diff<=k) return true;
            }
            hashmap[nums[i]]=i;
        }
        return false;
    }
};