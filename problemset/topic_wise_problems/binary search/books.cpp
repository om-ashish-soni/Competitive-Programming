// problem link : https://codeforces.com/problemset/problem/279/B
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n,m;cin>>n>>m;
    int pref[n+1];
    pref[0]=0;
    for(int i=1;i<=n;i++){
        cin>>pref[i];
        pref[i]+=pref[i-1];
    }
    int mx=0;
    for(int i=1;i<=n;i++){
        int stop=upper_bound(pref+i,pref+n+1,m+pref[i-1])-(pref+i);
        mx=max(mx,stop);
    }
    cout<<mx<<endl;
    return 0;
}
