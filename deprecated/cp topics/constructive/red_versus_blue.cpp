// problem link : https://codeforces.com/contest/1659/problem/A
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}
void solve(int t=0){
    int n,r,b;cin>>n>>r>>b;
    string s;
    int mod=r%(b+1);
    int div=r/(b+1);
    for(int i=0;i<=b;i++){
        for(int j=0;j<div;j++){
            s+="R";
        }
        if(i<mod){
            s+="R";
        }
        if(i<b){
            s+="B";
        }
    }
    cout<<s<<endl;
    
}
signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
    int t;cin>>t;
    while(t--){
        solve();    
    }
    return 0;
}
