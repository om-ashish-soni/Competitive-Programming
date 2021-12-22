// Problem link : https://www.codechef.com/DDUPP0001/problems/TACHSTCK
#include <bits/stdc++.h>
#define int long long int
#define endl "\n"
using namespace std;
int32_t main() {
    int n,k;
    cin>>n>>k;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    int pr=0;
    for(int i=0;i<n-1;){
        if(arr[i+1]-arr[i] <= k) {
            pr++;
            i+=2;
        }else{
            i++;
        }
    }
    cout<<pr<<endl;
	return 0;
}
