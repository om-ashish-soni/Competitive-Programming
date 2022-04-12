// problem link : https://codeforces.com/problemset/problem/1348/B
// solution : below code

#include <bits/stdc++.h>
using namespace std;
void reject(){
    cout<<-1<<endl;
    return;
}
void solve(){
    
    int n,k;cin>>n>>k;
    int arr[n];
    int overhead[n];
    vector<int> v;
    for(int i=0;i<n;i++){
        overhead[i]=0;
    }
    unordered_set<int> uns;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        uns.insert(arr[i]);
    }
    // cout<<"uns : "<<endl;
    // for(auto num:uns) cout<<num<<" ";cout<<endl;
    if(uns.size()>k) return reject();
    // cout<<"before making v"<<endl;
    if(uns.size()<k){
        int diff=k-uns.size();
        for(int j=0;j<diff;j++){
            v.push_back(arr[j]);
        }
    }
    // cout<<"after making v"<<endl;
    for(auto num:uns) v.push_back(num);
    // cout<<" v : "<<endl;
    // for(auto num:v) cout<<num<<" ";cout<<endl;
    int vi=k;
    for(int i=0;i<n;i++){
        while(arr[i] != v[vi-k]){
            v.push_back(v[vi-k]);
            vi++;
        }
        v.push_back(arr[i]);
        vi++;
    }
    cout<<v.size()<<endl;
    for(auto elem:v){
        cout<<elem<<" ";
    }
    cout<<endl;
}
int main() {
    int t;cin>>t;
    while(t--){
        solve();
    }
    return 0;
}

