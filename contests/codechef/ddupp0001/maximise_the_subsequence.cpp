// Problem link : https://www.codechef.com/DDUPP0001/problems/SIGNFLIP
#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve(){
    int n,k;
    cin>>n>>k;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    for(int i=0;i<k;i++){
        arr[i]=max(arr[i],-arr[i]);
    }
    int sum=0;
    for(int i=0;i<n;i++){
        if(arr[i]>0) sum+=arr[i];
    }
    cout<<sum<<endl;
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
