// problem link : https://codeforces.com/contest/1661/problem/A
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve(){
    int n;
    cin>>n;
    int cost=0;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    int b[n];
    for(int i=0;i<n;i++) cin>>b[i];
    for(int i=1;i<n;i++){
        cost+=min(abs(a[i]-a[i-1])+abs(b[i]-b[i-1]),abs(a[i]-b[i-1])+abs(b[i]-a[i-1]));
    }
    cout<<cost<<endl;
    
}
signed main() {
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}
