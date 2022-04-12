// problem link : https://codeforces.com/problemset/problem/507/B
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;


void solve(){
    int r,a,b,c,d;
    cin>>r>>a>>b>>c>>d;
    double numer=sqrt(((c-a)*(c-a) + (d-b)*(d-b)));
    cout<<ceil(numer/(2*r))<<endl;
}
signed main() {
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}
