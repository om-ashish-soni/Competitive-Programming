// problem link : https://codeforces.com/problemset/problem/1195/C
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;


void solve(){
    int n;
    cin>>n;
    int a[n],b[n];
    int dp[n][3];
    for(int i=0;i<n;i++){
        cin>>a[i];
        dp[i][0]=dp[i][1]=dp[i][2]=0;
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    dp[0][1]=a[0];
    dp[0][2]=b[0];
    for(int i=1;i<n;i++){
        dp[i][0]=max(dp[i-1][0],max(dp[i-1][1],dp[i-1][2]));
        dp[i][1]=max(dp[i-1][0]+a[i],dp[i-1][2]+a[i]);
        dp[i][2]=max(dp[i-1][0]+b[i],dp[i-1][1]+b[i]);
    }
    cout<<max(dp[n-1][0],max(dp[n-1][1],dp[n-1][2]));
    cout<<endl;
}
signed main() {
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}
