// problem link : https://leetcode.com/problems/random-pick-index/
// solution : below code
class Solution {
public:
    unordered_map<int,vector<int>> hashmp;
    Solution(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            hashmp[nums[i]].push_back(i);
        }
    }
    
    int pick(int target) {
        int seed=rand();
        vector<int>& indices=hashmp[target];
        int size=indices.size();
        return indices[(seed)%size];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
