// problem link : https://leetcode.com/problems/first-missing-positive/
// solution : below code

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n=nums.size()+2;
        vector<bool> v(n,false);
        for(auto num:nums) if(num>0 && num<n) v[num]=true;
        for(int i=1;i<n;i++) if(v[i]==false) return i;
        return -1;
    }
};
