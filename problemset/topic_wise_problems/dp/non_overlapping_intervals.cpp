// problem link : https://leetcode.com/problems/non-overlapping-intervals/description/
// solution : below code

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n=intervals.size();
        sort(intervals.begin(),intervals.end());
        vector<int> dp(n+1,INT_MAX);
        dp[n]=0;
        dp[n-1]=0;
        // for(int i=0;i<n;i++) cout<<intervals[i][0]<<" , "<<intervals[i][1]<<" } ";
        // cout<<endl;
        for(int i=n-1;i>=0;i--){
        
            int l=i+1;
            int r=n-1;
            int reach=i;
            while(l<=r){
                bool flag=(l==r);
                int mid=(l+r)/2;
                int index=mid;
                if(intervals[i][1] > intervals[index][0]){
                    reach=max(reach,index);
                    l=mid+1;
                }else{
                    r=mid;
                }
                if(flag) break;
            }
            
            int window=reach-i;
            dp[i]=window+dp[reach+1];
            if(reach != i){
                dp[i]=min(dp[i],dp[i+1]+1);
            }else{
                dp[i]=min(dp[i],dp[i+1]);
            }

            // cout<<i<<" to "<<reach<<" , dp[i] : "<<dp[i]<<endl;
        }
        return dp[0];
    }
};