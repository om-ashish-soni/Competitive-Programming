// Problem link : https://www.codechef.com/DDUPP0001/problems/HORSES
#include <bits/stdc++.h>
#define int long long 
using namespace std;
void solve(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    sort(arr,arr+n);
    int mn=LLONG_MAX;
    for(int i=1;i<n;i++){
        mn=min(mn,arr[i]-arr[i-1]);
    }
    cout<<mn<<endl;
}
int32_t main() {
    int t;
    cin>>t;
    while(t--){
        solve();
    }
	// your code goes here
	return 0;
}
