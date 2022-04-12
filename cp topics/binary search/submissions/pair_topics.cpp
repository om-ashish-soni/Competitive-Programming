// problem link : https://codeforces.com/problemset/problem/1324/D
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve(){
    int n;
    cin>>n;
    int a[n],b[n];
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    int v[n];
    for(int i=0;i<n;i++){
        v[i]=a[i]-b[i];
    }
    sort(v,v+n);
    int prs=0;
    for(int i=0;i<n;i++){
        int diff=a[i]-b[i];
        int up=n;
        if(diff<=0){
            up=upper_bound(v,v+n,-diff)-v;
            prs+=n-up;
        }else {
            up=upper_bound(v,v+n,-diff)-v;
            prs+=n-up-1;
        }
    }
    cout<<prs/2<<endl;
}
signed main() {
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}
