// problem link : https://codeforces.com/contest/1686/problem/A
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;read(n);
	int arr[n];read(arr,n);
	int sm=0;
	// map<int,bool> mp;
	F(i,0,n){
		sm+=arr[i];
		// mp[arr[i]]=true;
	}
	bool flag=false;
	// cout<<sm<<endl;
	F(i,0,n){
		// cout<<arr[i]*(n-1)<<" "<<sm-arr[i]<<endl;
		if(arr[i]*(n-1)==sm-arr[i]){
			flag=true;break;
		}
	}
	YESNO1(flag);
	
}
