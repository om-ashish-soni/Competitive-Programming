// problem link : https://leetcode.com/problems/maximum-earnings-from-taxi/description/
// solution : below code

class Solution {
public:
    #define ll long long 
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        vector<vector<pair<ll,ll>>> v(n+1);
        long long mx=0;
        for(auto & ride:rides){
            int l=ride[0];
            int r=ride[1];
            int val=ride[2];
            v[r].push_back({l,val});
        }
        vector<long long> dp(n+1,0);
        for(int i=1;i<=n;i++){
            dp[i]=dp[i-1];
            vector<pair<ll,ll>> & row=v[i];
            for(auto & pr:row){
                ll l=pr.first;
                ll val=pr.second;
                ll window=i-l;
                ll score=window+val;
                score+=dp[l];
                dp[i]=max(dp[i],score);
            }
            mx=max(mx,dp[i]);
        }
        // for(int i=0;i<=n;i++){
        //     cout<<dp[i]<<" ";
        // }
        // cout<<endl;
        return mx;
    }
};