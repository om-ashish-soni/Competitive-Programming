// problem link : https://leetcode.com/problems/maximum-width-ramp/description/
// solution : below code

class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n=nums.size();
        vector<int> dp(n,0);
        dp[n-1]=n-1;
        set<pair<int,int>> s;
        s.insert({nums[n-1],n-1});
        for(int i=n-2;i>=0;i--){
            dp[i]=i;
            auto it=s.lower_bound({nums[i],0});
            if(it != s.end()){
                int index=it->second;
                dp[i]=dp[index];
            }
            s.insert({nums[i],i});
        }
        int mx=0;
        for(int i=0;i<n;i++){
            int window=dp[i]-i;
            mx=max(mx,window);
        }
        return mx;
    }
};