// problem link : https://codeforces.com/problemset/problem/327/A
// solution : below code
// time taken : 25 m 38 s


void solve(int t){
	//shree ganeshay namah
	int n;
	cin>>n;
	int a[n];
	read(a,n);
	int one=count(ALLA(a,n),1);
	int z=0,o=0;
	int diff_upto_now=0;
	int diff=0;
	F(i,0,n){
		int cur=1;
		if( a[i]==1) cur=-1;
		diff_upto_now=max(0LL,diff_upto_now+cur);
		diff=max(diff_upto_now,diff);
		
		// cout<<"at "<<i<<" diff : "<<diff<<endl;
	}
	// cout<<diff<<endl;
	if(one==n){
		cout<<one-1<<endl;
	}else{
		cout<<diff+one<<endl;	
	}
	
}
