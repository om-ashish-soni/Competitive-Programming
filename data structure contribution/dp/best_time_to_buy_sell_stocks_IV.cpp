// problem link : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/submissions/
// solution : below code

class Solution {
public:
    int maxProfit(int k, vector<int>& p) {
        if(p.size()==0) return 0;
        vector<int> v={p[0]};
        for(int i=1;i<p.size()-1;i++){
            if(p[i]==v.back());
            else if(p[i]>v.back() && p[i]<p[i+1]);
            else if(p[i]<v.back() && p[i]>p[i+1]);
            else v.push_back(p[i]);
        }
        v.push_back(p[p.size()-1]);
        for(auto num:v) cout<<num<<" ";cout<<endl;
        int mx=0;
        int n=v.size();
        vector<vector<int>> dp(n,vector<int>(k+1,0));
        for(int i=1;i<n;i++){
            dp[i]=dp[i-1];
            for(int j=i-1;j>=0;j--){
                int diff=v[i]-v[j];
                if(diff>0){
                    for(int m=0;m<k;m++){
                        dp[i][m+1]=max(dp[i][m+1],diff+dp[j][m]);
                        mx=max(dp[i][m+1],mx);
                    }
                }
            }
        }
        return mx;
    }
};
