// problem link : https://leetcode.com/problems/find-the-duplicate-number/
// solution : below code
class Solution {
public:
    int findDuplicate(vector<int>& nums,int i=0) {
        vector<bool> container(nums.size(),false);
        for(auto num:nums){
            if(container[num]) return num;
            container[num]=true;
        }
        return -1;
    }
};
