// problem link : https://codeforces.com/contest/1673/problem/C
// solution : below code

#include <bits/stdc++.h>
#define int long long
#define ll long long
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
string intToString(int n){
    ostringstream om;
    om<<n;
    return om.str();
}
bool checkPalindrome(string s){
    string copy=s;
    reverse(begin(copy), end(copy));
    return s==copy;
}
int modMul(int a,int b,int mod){
    return (a%mod + b%mod)%mod;
}
vector<int> pal;
int MAX=4e4 + 10;
vector<int> dp(MAX,0);
void solve(){
    // int n;cin>>n;
    
    // cout<<dp[n]<<endl;
}   

signed main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif

    
    for(int i=1;i<=MAX;i++){
        string num=intToString(i);
        if(checkPalindrome(num)){
            pal.push_back(i);
        }
    }
    // for(auto num:pal) cout<<num<<" ";cout<<endl;
    
    int MOD=1e9 + 7;
    int psize=pal.size();
    // cout<<"pszie : "<<psize<<endl;
    // MAX=10;
    vector< vector< ll > > dp(pal.size(),vector<int>(MAX+1,0));
    for(ll i=0 ; i<=MAX ; i++)
        dp[0][i] = 1;
    for(ll i=1 ; i<dp.size() ; i++){
        for(ll j=0 ; j<=MAX ; j++){
            if( j<pal[i] )
                dp[i][j] = dp[i-1][j];
            else{
                dp[i][j] = (dp[i-1][j]%MOD+dp[i][j-pal[i]]%MOD)%MOD;
            }
        }
    }
    // for(int i=0;i<pal.size();i++){
    //     for(int j=0;j<=MAX;j++) cout<<dp[i][j]<<" ";cout<<endl;
    // }
    // cout<<endl;
    int t=1;
    cin>>t;
    while(t--){
        int n;cin>>n;
        cout<<dp.back()[n]<<endl;
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
    return 0;
}
