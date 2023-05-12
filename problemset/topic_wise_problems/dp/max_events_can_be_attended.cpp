// problem link : https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/description/
// solution : below code

                        
class Solution {
public:
    #define ll long long
    #define map unordered_map
    int compress(vector<vector<int>>& events){
        set<int> s;
        for(auto & event:events){
            s.insert(event[0]);
            s.insert(event[1]);
        }
        int key=0;
        map<int,int> mp;
        mp.reserve(s.size()+10);
        for(auto num:s){
            key++;
            mp[num]=key;
        }
        for(auto & event:events){
            event[0]=mp[event[0]];
            event[1]=mp[event[1]];    
        }
        return s.size()+10;
    }
    int maxValue(vector<vector<int>>& events, int k) {
        ll n=events.size();
        ll mx=0;
        ll sz=compress(events);
        vector<vector<pair<ll,ll>>> v(sz);
        vector<vector<ll>> dp(sz,vector<ll>(k+1,0));
        for(auto & event:events){
            ll l=event[0];
            ll r=event[1];
            ll val=event[2];
            v[r].push_back({l,val});
        }
        for(int i=0;i<sz;i++){
            if(i>0) dp[i]=dp[i-1];
            vector<pair<ll,ll>> & row=v[i];
            for(auto & pr:row){
                ll l=pr.first;
                ll score=pr.second;
                for(int j=1;j<=k;j++) dp[i][j]=max(dp[i][j],score);
                if(l-1>=0){
                    for(int j=0;j<k;j++){
                        dp[i][j+1]=max(dp[i][j+1],dp[l-1][j]+score);
                    }
                }
                
            }
            for(int j=0;j<=k;j++){
                mx=max(mx,dp[i][j]);
            }
        }
        return mx;
    }
};