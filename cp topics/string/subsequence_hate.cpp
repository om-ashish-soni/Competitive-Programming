// problem link : https://codeforces.com/problemset/problem/1363/B
// solution : below code
#include <bits/stdc++.h>
#define int long long
using namespace std;


void solve(){
    
    string s;cin>>s;
    int n=s.size();
    if(n==1){
        cout<<0<<endl;
        return;
    }
    int one=0,zero=0;
    int po[n],pz[n],so[n],sz[n];
    if(s[0]=='0'){
        pz[0]=1;
        po[0]=0;
    }else{
        pz[0]=0;
        po[0]=1;
    }
    if(s[n-1]=='0'){
        sz[n-1]=1;
        so[n-1]=0;
    }else{
        sz[n-1]=0;
        so[n-1]=1;
    }
    for(int i=1;i<n;i++){
        po[i]=po[i-1];
        pz[i]=pz[i-1];
        if(s[i]=='0'){
            pz[i]++;
        }else{
            po[i]++;
        }
    }
    for(int i=n-2;i>=0;i--){
        so[i]=so[i+1];
        sz[i]=sz[i+1];
        if(s[i]=='0'){
            sz[i]++;
        }else{
            so[i]++;
        }
    }
    int mn=min(sz[0],so[0]);
    
    for(int i=0;i<n-1;i++){
        mn=min(mn,min(po[i]+sz[i+1],pz[i]+so[i+1]));
    }
    cout<<mn<<endl;
}
signed main() {
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
}
