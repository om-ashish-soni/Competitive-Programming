// problem link : https://codeforces.com/problemset/problem/1285/C
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;

int lcm(int a,int b){
    return (a*b)/__gcd(a,b);
}
void solve(){
    int n;
    cin>>n;
    if(n==1){
        cout<<1<<" "<<1<<endl;
    }
    int divider=ceil(sqrt(n))-1;
    while(divider>0){
        if(lcm(divider,n/divider)==n){
            cout<<divider<<" "<<n/divider<<endl;
            return;
        }
        divider--;
    }
    
}
signed main() {
    int t=1;
    // cin>>t;
    while(t--){
        solve();
    }
}
