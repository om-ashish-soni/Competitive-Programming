// problem link : https://codeforces.com/problemset/problem/474/B
// solution : below code
// time taken : 6 m 25 s

void solve(int t){
	//shree ganeshay namah
	int n;
	cin>>n;
	int arr[n];
	read(arr,n);
	int m;read(m);
	int b[m];read(b,m);
	F(i,1,n) arr[i]+=arr[i-1];
	// println(arr,n);
	F(i,0,m){
		int num=b[i];
		int index=lower_bound(arr,arr+n,num)-arr;
		cout<<index+1<<endl;
	}
	
}
