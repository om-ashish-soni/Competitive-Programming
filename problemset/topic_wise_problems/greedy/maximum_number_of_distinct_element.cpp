// Problem link : https://www.codechef.com/problems/MAXDISTKT
// Problem type : Greedy
#include <bits/stdc++.h>
#define int long long int
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
#define vpi             vector<pair<int,int>> 
#define dbg(x)           cout<<x<<" = "<<x<<endl
/*

 ___________________________________________________________
| AUTHOR  : Om Ashish Soni                                  |
| code    : C++14                                           |
| IDE     : Online IDE                                      | 
|___________________________________________________________|

*/
using namespace std;
class class_name
{
    int n,count,*arr;
    string s;
    public:
    static bool comp(pair<int,int>&p1,pair<int,int>&p2){
        return p1.first<p2.first;
    }
    static bool reverseComp(pair<int,int>&p1,pair<int,int>&p2){
        return p1.second<p2.second;
    }
    class_name()
    {
        int n;
        cin>>n;
        vpi b(n);
        rep(i,n,1){
            int num;
            cin>>num;
            b[i]=make_pair(num,i);
        }
        sort(b.begin(),b.end(),comp);
        int validA=0;
        rep(i,n,1){
            validA=min(validA,b[i].first-1);
            b[i].first=validA;
            validA++;
        }
        sort(b.begin(),b.end(),reverseComp);
        rep(i,n,1) cout<<b[i].first<<" "; cout<<endl;
        // arr=new int[n];
    }
    ~class_name(){
        // delete[] arr;
    }
};
int32_t main() {
    int t;
    cin>>t;
    while(t--) class_name object_name;
	return 0;
}
