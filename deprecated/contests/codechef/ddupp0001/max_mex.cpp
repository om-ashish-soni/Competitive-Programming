// Problem link : https://www.codechef.com/DDUPP0001/problems/MEX
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
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    int index=0;
    int i=0;
    for(i=0;index<n;){
        if(arr[index]>i){
            if(k>0) k--;
            else break;
            i++;
        }else if(arr[index] == i){ index++;i++;}
        else index++;
    }
    cout<<i+k<<endl;
}
int32_t main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
