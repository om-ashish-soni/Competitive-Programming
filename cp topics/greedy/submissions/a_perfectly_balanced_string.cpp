// problem link : https://codeforces.com/contest/1673/problem/B
// solution : below code
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define endl "\n"
using namespace std;
void print(bool b){
    if(b) cout<<"YES";
    else cout<<"NO";
    cout<<endl;
}
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}
void reject(){
    cout<<-1<<endl;return; 
}
void makePermutation(int *arr,int n){
    for(int i=0;i<n;i++) arr[i]=i+1;
}
void printArray(int *arr,int n){
    for(int i=0;i<n;i++) cout<<arr[i]<<" ";cout<<endl;
}
int getScore(string s,int start,int end){
    int score=0;
    for(int i=start;i<=end;i++){
        score+=s[i]-'a'+1;
    }
    return score;
}
void solve(){
    string s;cin>>s;
    int n=s.size();
    unordered_map<char,vector<int>> hash;
    for(int i=0;i<n;i++){
        hash[s[i]].push_back(i);
    }
    // int diff=hash.begin()->second
    int diff=hash.size();
    for(char c='a';c<='z';c++){
        vector<int>& v=hash[c];
        int sz=v.size();
        for(int i=0;i<sz-1;i++){
            int temp_diff=v[i+1]-v[i];
            
            if(diff!=temp_diff){
                return print(false);
            }
        }
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
