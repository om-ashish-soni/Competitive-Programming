// problem link : https://codeforces.com/problemset/problem/1669/H
// solution : below code
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}

void solve(int t=0){
    int n;cin>>n;
    int k;cin>>k;
    int arr[n];
    scan(arr,n);
    vector<int>v(32,0);
    for(int i=0;i<n;i++){
        bitset<32> bs(arr[i]);
        for(int j=0;j<31;j++){
            v[j]+=bs[j];
        }
    }
    bitset<32> ans;
    // for(int i=31;i>=0;i--){
    //     cout<<v[i]<<" ";
    // }
    // cout<<endl;
    for(int i=30;i>=0;i--){
        if(n-v[i]<=k){
            ans.set(i);
            k-=n-v[i];
        }
    }
    cout<<ans.to_ullong()<<endl;
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
