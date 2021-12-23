// Problem link : https://www.codechef.com/INFI21B/problems/DALGONA
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
void solve(){
    int n;
    cin>>n;
    double sqroot=sqrt(n);
    if(n==1){
        cout<<1<<endl;
        cout<<1<<" "<<1<<endl;
    }else if(n==2){
        cout<<2<<endl;
        cout<<3<<" "<<1<<endl;
        cout<<4<<" "<<1<<endl;
    }else if(ceil(sqroot)==floor(sqroot)){
        cout<<1<<endl;
        cout<<1<<" "<<n<<endl;
    }else if(n%2 == 0){
        cout<<2<<endl;
        cout<<1<<" "<<n-1<<endl;
        cout<<(n/2 - 1)<<" "<<1<<endl;
    }else {
        cout<<2<<endl;
        cout<<2<<" "<<n-1<<endl;
        cout<<n-2<<" "<<1<<endl;
    }
}
int32_t main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
