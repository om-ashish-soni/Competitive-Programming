// Problem link : https://codeforces.com/contest/1673/problem/A
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
    int score=0;
    int n=s.size();
    if(n==1){
        cout<<"Bob"<<" "<<s[0]-'a'+1<<endl;
        return;
    }
    cout<<"Alice"<<" ";
    if(n%2==0){
        cout<<getScore(s,0,n-1);
    }else{
        if(s[0]<s[n-1]){
            cout<<getScore(s,1,n-1)-getScore(s,0,0);
        }else{
            cout<<getScore(s,0,n-2)-getScore(s,n-1,n-1);
        }
    }
    cout<<endl;
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
