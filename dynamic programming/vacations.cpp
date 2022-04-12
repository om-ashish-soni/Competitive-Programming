// problem link : https://codeforces.com/problemset/problem/698/A
// solution : below code

#include <iostream>
using namespace std;

int main() {
    int n;cin>>n;
    int arr[n];
    int dp[n+1][3];
    for(int i=0;i<3;i++){
        dp[n][i]=0;
    }
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    for(int i=n-1;i>=0;i--){
        dp[i][0]=max(dp[i+1][1],max(dp[i+1][2],dp[i+1][0]));
        dp[i][1]=dp[i+1][1];
        dp[i][2]=dp[i+1][2];
        if(arr[i]==0){
            dp[i][1]=dp[i+1][2];
            dp[i][2]=dp[i+1][1];
            
        }
        if(arr[i]==1 or arr[i]==3){
            dp[i][1]=max(dp[i][1],max(1+dp[i+1][2],1+dp[i+1][0]));
        }
        if(arr[i]==2 or arr[i]==3){
            dp[i][2]=max(dp[i][2],max(1+dp[i+1][1],1+dp[i+1][0]));
        }
        // cout<<i<<" : "<<endl;
        // cout<<dp[i][0]<<" "<<dp[i][1]<<" "<<dp[i][2]<<endl;
    }
    int mx=max(dp[0][0],max(dp[0][1],dp[0][2]));
    cout<<n-mx<<endl;
    // your code goes here
    return 0;
}
