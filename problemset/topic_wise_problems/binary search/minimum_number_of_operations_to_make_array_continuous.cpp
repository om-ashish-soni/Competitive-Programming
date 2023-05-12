// problem link : https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/
// solution : below code

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n=nums.size();
        sort(nums.begin(),nums.end());
        set<int> s;
        for(auto num:nums) s.insert(num);
        vector<int> v;
        for(auto num:s) v.push_back(num);
        for(auto num:v) cout<<num<<" ";cout<<endl;
        unordered_map<int,int> hash1,hash2;
        int mn=n+1;
        
        for(int i=0;i<n;i++){
            int lower_limit=nums[i];
            int upper_limit=nums[i]+n-1;
            int l=lower_bound(v.begin(),v.end(),lower_limit)-v.begin();
            int r=upper_bound(v.begin(),v.end(),upper_limit)-v.begin();
            // cout<<"i : "<<i<<" , l : "<<l<<" vs r : "<<r<<endl;
            int window=r-l;
            mn=min(mn,n-window);
        }
        return mn;
    }
};
