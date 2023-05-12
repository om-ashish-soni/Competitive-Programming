// problem link : https://codeforces.com/contest/1673/problem/D
// solution : below code

#include <bits/stdc++.h>
#define int long long
#define ll long long
#define pii pair<int,int>
#define endl "\n"
using namespace std;
void infinite(){
    cout<<-1<<endl;
}
void notexist(){
    cout<<0<<endl;
}
bool isin(int a,int d,int n,int term){
    int temp=(term - a);
    if(temp%d) return false;
    int n_term=temp/d + 1;
    return n_term>0 and n_term<=n;
}
void findAllFactors(int n,std::vector<int>& factors){
    double sqroot=sqrt(n);
    factors.push_back(1);
    for(int i=2;i<=sqroot;i++){
        if(n%i == 0){
            factors.push_back(i);
            if(n/i != i){
                factors.push_back(n/i);
            }
        }
    }
    factors.push_back(n);
    sort(factors.begin(),factors.end());
}
pair<int,int> extended_gcd(int a,int b){
    if(b==0) return{1,1};
    pair<int,int> pr=extended_gcd(b,a%b);
    return {pr.second,pr.first-(a/b)*pr.second};
}
int modInv(int a,int mod){
    int x,y;
    pair<int,int> pr=extended_gcd(a,mod);
    x=pr.first;
    y=pr.second;
    int g=(a*x + mod*y);
    if(g!=1){
        cerr<<"modular inverse does not exist , gcd != 1"<<endl;
        exit(0);
    }
    // adding m to avoid negative value of x 
    int res=(x%mod + mod)%mod;
    return res;
}
int modDiv(int a,int b,int mod){
    
    a=a%mod;
    int inv=modInv(b,mod);
    int res=(inv*a)%mod;
    return res;
}
int modMul(int a,int b,int mod){
    return ((a%mod)*(b%mod))%mod;
}
int modAdd(int a,int b,int mod){
    return ((a%mod)+(b%mod))%mod;
}
int lcm(int a,int b){
    return (a*b)/(__gcd(a,b));
}
void solve(){
    const int MOD=(1e9)+7;
    int ba,bd,bn;
    int ca,cd,cn;
    cin>>ba>>bd>>bn;
    cin>>ca>>cd>>cn;
    if(cd%bd){
        return notexist();
    }
    if(isin(ba,bd,bn,ca)==false or isin(ba,bd,bn,ca+(cn-1)*cd)==false){
        return notexist();
    }
    if(isin(ba,bd,bn,ca-cd)==false or isin(ba,bd,bn,ca+(cn*cd))==false){
        return infinite();
    }
    // cout<<"finite"<<endl;
    vector<int> factors;
    findAllFactors(cd,factors);
    int ans=0;
    int mx=1e9;
    int mn=-mx;
    for(auto num:factors){
        if(lcm(num,bd)!=cd) continue;
        int division=modDiv(cd,num,MOD);
        ans=modAdd(ans,modMul(division,division,MOD),MOD);
    }
    cout<<ans<<endl;
}   

signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif

    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
    return 0;
}
