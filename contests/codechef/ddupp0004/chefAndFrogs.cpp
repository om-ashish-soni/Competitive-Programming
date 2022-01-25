#include <bits/stdc++.h>
#define int long long 
#define ll long long
#define endl "\n"

/*

 ___________________________________________________________
| AUTHOR  : Om Ashish Soni                                  |
| code    : C++14                                           |
| IDE     : Sublime txt                                     | 
|___________________________________________________________|

*/
using namespace std;
map<pair<int,int>,bool> memo;
void yes(){
    cout<<"Yes"<<endl;
}
void no(){
    cout<<"No"<<endl;
}
void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}
void solve(){
    memo.clear();
    int n,k,p;
    cin>>n>>k>>p;
    int maxCon[n+1];
    int arr[n+1];
    vector<pair<int,int>> v(n);
    for(int i=0;i<n;i++) cin>>v[i].first,v[i].second=i+1;
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++) arr[v[i].second]=i;
    maxCon[v[n-1].second]=v[n-1].first;
    for(int i=n-2;i>=0;i--) 
        if(v[i+1].first-v[i].first<=k) maxCon[v[i].second]=maxCon[v[i+1].second]; 
        else maxCon[v[i].second]=v[i].first;
    
    for(int i=0;i<p;i++){
        int a,b;
        cin>>a>>b;
        if(arr[a]>arr[b]) swap(a,b);
        if(maxCon[a]>=v[arr[b]].first) yes();
        else no();
    }
}
int32_t main() {
    solve();
    return 0;
}
