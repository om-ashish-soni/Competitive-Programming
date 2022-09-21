// problem link : https://leetcode.com/problems/best-team-with-no-conflicts/
// solution : below code


class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int mx=0;
        int n=scores.size();
        vi dp(n,0);
        vpii v(n);
        F(i,0,n){
            v[i]={scores[i],ages[i]};
        }
        SORT(v);
        dp[0]=v[0].first;
        F(i,1,n){
            dp[i]=v[i].first;
            F(j,0,i){
                if(v[i].second>=v[j].second){
                    dp[i]=max(dp[i],dp[j]+v[i].first);
                }else if(v[i].first<=v[j].first){
                    dp[i]=max(dp[i],dp[j]+v[i].first);
                }
            }
        }
        FEACH(num,dp) mx=max(mx,num);
        return mx;
    }
};
