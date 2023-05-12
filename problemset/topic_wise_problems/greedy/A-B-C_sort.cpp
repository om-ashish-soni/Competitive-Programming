// problem link : https://codeforces.com/problemset/problem/1674/D
// solution : below code

#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
void print(bool b){
    if(b) cout<<"YES";
    else cout<<"NO";
    cout<<endl;
}
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}

void solve(){
    int n;cin>>n;int arr[n];scan(arr,n);
    int start=0;
    if(n%2) start=1;
    for(int i=start;i<n;i+=2){
        if(arr[i]>arr[i+1]) swap(arr[i],arr[i+1]);
    }
    for(int i=0;i<n-1;i++){
        if(arr[i]>arr[i+1]) return print(false);
    }
    return print(true);
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
    return 0;
}
