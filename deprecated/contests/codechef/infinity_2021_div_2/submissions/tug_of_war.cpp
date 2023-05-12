// Problem link : https://www.codechef.com/INFI21B/problems/TOW
// Problem type : binary search, constructive ,two pointers
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
void yes(){
    cout<<"YES"<<endl;
}
void no(){
    cout<<"NO"<<endl;
}
void solve(){
    int m,n;
    cin>>n>>m;
    int a[n],b[m];
    int mxa=0,mxb=0;
    int mxaindex=0;
    int lasta=0;
    for(int i=0;i<n;i++){ cin>>a[i];if(a[i]>mxa){mxa=a[i];mxaindex=i;}}
    for(int i=0;i<m;i++){ cin>>b[i];mxb=max(mxb,b[i]);}
    if(mxa>mxb){
        return no();
    }else if(mxa<mxb){
        yes();
        sort(b,b+m);
        for(int i=0;i<m;i++) cout<<b[i]<<" "; cout<<endl;
        return;
    }else{
        int mxafreq=0;
        int mxbfreq=0;
        int firsta=n;
        for(int i=0;i<n;i++){if(mxa == a[i]){firsta=min(i,firsta); mxafreq++;lasta=i;}}
        for(int i=0;i<m;i++){if(mxb == b[i]) mxbfreq++;}
        if(mxafreq>mxbfreq) return no();
        else if(mxafreq<mxbfreq){
            yes();
            sort(b,b+m);
            for(int i=0;i<m;i++) cout<<b[i]<<" "; cout<<endl;
            return;
        }else{
            vector<int> modified;
            int temp=lasta;
            for(int i=0;i<m;i++){
                if(mxb!=b[i]) modified.push_back(b[i]);
            }
            sort(modified.begin(),modified.end());
            reverse(modified.begin(),modified.end());
            int currb=0;
            lasta=temp+1;
            while(currb<modified.size() && lasta<n){
                if(modified[currb]<a[lasta]){
                    // cout<<modified[currb]<<" ??? "<<a[lasta]<<endl;
                    return no();
                }else if(modified[currb]==a[lasta]){
                    lasta++;
                    currb++;
                }
                else lasta++;
            }
            if(currb>=modified.size()){
                return no();
            }else{
                yes();
                for(int i=modified.size()-1;i>currb;i--){
                    cout<<modified[i]<<" ";
                }
                for(int i=0;i<mxbfreq;i++) cout<<mxb<<" ";
                for(int i=0;i<=currb;i++) cout<<modified[i]<<" ";
                cout<<endl;
            }
        }
    }
}
int32_t main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
