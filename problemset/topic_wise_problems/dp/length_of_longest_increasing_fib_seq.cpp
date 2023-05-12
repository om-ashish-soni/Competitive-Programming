// problem link : https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/description/
// solution : below code


class Solution {
public:
    
    int lenLongestFibSubseq(vector<int>& arr) {
        int n=arr.size();
        map<int,int> mp;
        vector<map<int,int>> dp(n);
        for(int i=0;i<n;i++){
            mp[arr[i]]=i;
        }
        int mx=0;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int sm=arr[i]+arr[j];
                int delta=arr[i]-arr[j];
                if(mp.count(sm)){
                    int index=mp[sm];
                    if(dp[j].count(i)==0) dp[j][i]=0;
                    int len=dp[j][i]+1;
                    dp[index][j]=len;
                    cout<<arr[i]<<" to "<<arr[j]<<" to "<<arr[index]<<" : "<<len<<endl;
                    mx=max(mx,len);
                }
            }
            mp[arr[i]]=i;
        }
        // cout<<mx<<endl;
        mx+=2;
        if(mx>=3) return mx;
        return 0;
    }
};