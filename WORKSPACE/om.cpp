#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
using namespace std;
void scan(int *arr,int n){
    for(int i=0;i<n;i++) cin>>arr[i];
}
void print(bool b){
    if(b) cout<<"YES";
    else cout<<"NO";
    cout<<endl;
}
pii convert(int n){
    if(n==0) return {0,0};
    if(n==1) return {1,2};
    if(n==2) return {3,4};
    if(n==3) return {5,5};
    return {0,0};
}
bool dothis(vector<vector<bool>>& v,vector<int> arr,int n,int start){
    arr[0]=start;
    for(int i=1;i<n;i++){
        pii pr=convert(arr[i]);
        // cout<<pr.first<<" "<<pr.second<<endl;
        if(v[arr[i-1]][pr.first]){
            arr[i]=pr.first;
        }else if(v[arr[i-1]][pr.second]){
            arr[i]=pr.second;
        }else return false;
    }
    
    return true;
}
bool checkout(vector<int>& v,int n){
    // cout<<n<<endl;
    if(n==0) return true;
    if(n<0) return false;
    for(auto num:v){
        if(n%num==0){
            return true;  
        } 
    }
    return false;
}
int getmsb(int n){
    if(n==0) return 32;
    return (int)log2(n);
}
void reject(){ cout<<-1<<endl;}
void solve(){
    int n;cin>>n;int arr[n];scan(arr,n);
    int v[4]={0,0,0,0};
    int sm=0;
    for(int i=0;i<n;i++){
        v[arr[i]%4]++;
        sm+=arr[i];
    }
    if(sm%4) return reject();
    // cout<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]<<endl;
    int steps=0;
    v[0]=0;
    

    int com13=min(v[1],v[3]);
    steps+=com13;
    v[1]-=com13;
    v[3]-=com13;
    
    int com12=min(v[2]*2,v[1]);
    steps+=com12;
    v[2]-=com12/2;
    v[1]-=com12;

    int com32=min(v[2]*2,v[3]);
    steps+=com32;
    v[2]-=com32/2;
    v[3]-=com32;
    
    // cout<<v[0]<<","<<v[1]<<","<<v[2]<<","<<v[3]<<endl;

    steps+=(v[2]/2);
    v[2]=v[2]%2;
    steps+=(v[1]/4)*3;
    v[1]=v[1]%4;
    steps+=(v[3]/4)*3;
    v[3]=v[3]%4;
    cout<<steps<<endl;
    return;
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