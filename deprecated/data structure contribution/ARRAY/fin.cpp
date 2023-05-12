class Solution {
public:
    int findDuplicate(vector<int>& nums,int i=0) {
        if(!i) sort(nums.begin(),nums.end());
        return (nums[i] == nums[i+1])?(nums[i]):(findDuplicate(nums,1+i));
    }
};