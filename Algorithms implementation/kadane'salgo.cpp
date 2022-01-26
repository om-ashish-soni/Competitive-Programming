#include<bits/stdc++.h>
using namespace std;
int findMinSubArray(int i,int n,int *arr){
    int mn_so_far=INT_MAX;
    int curr_mn=INT_MAX;
    for(;i<n;i++){
        if(curr_mn>0){
            curr_mn=arr[i];
        }else{
            curr_mn+=arr[i];
        }
        mn_so_far=min(mn_so_far,curr_mn);
    }
    return mn_so_far;
}
int main()
 {
	//code
	int t;
	cin>>t;
	while(t--){
	    int n;
	    cin>>n;
	    int arr[n];
	    for(int i=0;i<n;i++) cin>>arr[i];
	    for(int i=0;i<n;i++){
	        cout<<findMinSubArray(i,n,arr)<<" ";
	    }cout<<endl;
	}
	return 0;
}
