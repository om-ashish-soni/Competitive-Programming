// Problem link : https://codeforces.com/contest/1615/problem/B
// Problem type : bitmask, greedy, math
#include <bits/stdc++.h>
#define int long long 
#define ll long long
#define endl "\n"
#define rep(i,n,k)       for(ll i=0;i<n;i+=k)
#define rrep(i,n,k)      for(ll i=n;i>=0;i-=k)
#define rep1(i,n,k)      for(ll i=1;i<n;i+=k)
#define vi               vector<int>
#define vl               vector<ll>
#define vs               vector<string>
#define vvi              vector<vi>
#define fast             ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define pb               push_back
#define mp               make_pair
#define ff                first
#define se                second
#define maxn              1e6+3
#define inf               1e18
#define modulo               1e9+7
#define pi               3.1415926535897932384626433832795
#define testcase(t)     long long t;cin>>t;while(t--)
#define mem(dp,i)        memset(dp,i,sizeof(dp))
#define all(x)           (x).begin(), (x).end()
#define dbg(x)           cout<<x<<" = "<<x<<endl
/*
 ___________________________________________________________
| AUTHOR  : Om Ashish Soni                                  |
| code    : C++14                                           |
| IDE     : Sublime txt                                     | 
|___________________________________________________________|
*/
using namespace std;
void solve(vector<vector<int>>& pref){
    int l,r;
    cin>>l>>r;
    int ans=0;
    for(int i=0;i<20;i++){
        ans=max(ans,pref[r][i]-pref[l-1][i]);
    }
    cout<<r-l+1-ans<<endl;
}
int32_t main() {
    int t;
    // cout<<" hello"<<endl;
    vector<int> row(20);
    vector<vector<int>> pref(200010,row);
    for(int j=0;j<20;j++) pref[0][j]=0;
    for(int i=1;i<200010;i++){
        int num=i;
        for(int j=0;j<20;j++){
            pref[i][j]=pref[i-1][j]+(num&1);
            num>>=1;
        }
    }
    for(cin>>t;t;t--) solve(pref);
    return 0;
}