// problem link : https://leetcode.com/problems/split-array-largest-sum/description/
// solution : below code

class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int sm=0;
        int mx=0;
        for(auto num:nums){
            sm+=num;
            mx=max(mx,num);
        }
        int avg=max(mx,(sm+k-1)/k);
        int ans=mx;
        int window=0;

        int n=nums.size();
        #define ll long long 
        const int inf=1e10+10;
        vector<vector<ll>> dp(n+1,vector<ll>(k+1,inf));
        for(int j=0;j<=k;j++) dp[n][j]=0;
        for(int i=n-1;i>=0;i--){
            ll sm=nums[i];
            for(int j=i+1;j<=n;j++){
                for(int m=1;m<=k;m++){
                    dp[i][m]=min(dp[i][m],dp[j][m]+sm);
                    if(m+1<=k) dp[i][m+1]=min(dp[i][m+1],max(dp[j][m],sm));
                }
                if(j<n)sm+=nums[j];
            }
        }
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<=k;j++) cout<<dp[i][j]<<" ";
        //     cout<<endl;
        // }
        return dp[0][k];
    }
};