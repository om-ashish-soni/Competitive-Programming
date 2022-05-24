// problem link : https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
// solution : below code

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n=nums.size()+1;
        vector<bool> v(n,false);
        for(auto num:nums) v[num]=true;
        vector<int> missing;
        for(int i=1;i<n;i++) if(v[i]==false) missing.push_back(i);
        return missing;
    }
};
