// problem link : https://leetcode.com/problems/partition-array-for-maximum-sum/
// solution : below code

class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int> dp(n,0);
        dp[0]=arr[0];
        for(int i=1;i<n;i++){
            int limit=max(-1,i-k);
            int mx=arr[i];
            dp[i]=arr[i]+dp[i-1];
            int window=1;
            for(int j=i-1;j>limit;j--){
                mx=max(mx,arr[j]);
                window++;
                dp[i]=max(dp[i],(mx*window)+((j-1>=0)?dp[j-1]:0));
            }
        }
        return dp[n-1];
    }
};
