// problem link : https://codeforces.com/problemset/problem/1374/D
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;


void solve(){
    int n,k;
    cin>>n>>k;
    int arr[n];
    map<int,int> ump;
    int remaining=n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(arr[i]%k) ump[k-arr[i]%k]++;

    }
    pair<int,int> mxpair;
    for(auto &pr:ump){
        if(pr.second>mxpair.second){
            mxpair=pr;
        }else if(pr.second==mxpair.second){
            mxpair.first=max(mxpair.first,pr.first);
        }
    }
    // cout<<mxpair.first<<" "<<mxpair.second<<endl;
    int x=0;
    if(mxpair.second>0) x=k*(mxpair.second-1) + mxpair.first + 1;
    cout<<x<<endl;
}
signed main() {
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}
