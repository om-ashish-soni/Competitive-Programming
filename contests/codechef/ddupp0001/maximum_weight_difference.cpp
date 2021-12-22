// Problem link : https://www.codechef.com/DDUPP0001/problems/MAXDIFF
#include <bits/stdc++.h>
#define int long long
using namespace std;
void printV(std::vector<int> &v){
    for(auto num:v){
        cout<<num<<" ";
    }
    cout<<endl;
    return;
}
void convert(int n,std::vector<int> &v){
    while(n>0){
        v.push_back(n&1);
        n>>=1;
    }
}
void solve(){
    int n,k;
    cin>>n>>k;
    k=min(k,n-k);
    int arr[n];
    int sum=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        sum+=arr[i];
    }
    sort(arr,arr+n);
    int ksum=0;
    for(int i=0;i<k;i++){
        ksum+=arr[i];
    }
    cout<<abs(sum-2*ksum)<<endl;
    return;
}
int32_t main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
