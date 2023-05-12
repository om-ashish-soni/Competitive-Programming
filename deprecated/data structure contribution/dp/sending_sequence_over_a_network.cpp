// problem link : https://codeforces.com/contest/1741/problem/E
// solution : below code

void solve(int t){
	//shree ganeshay namah
	//println("shree ganeshay namah");
	int n;
	read(n);
	vi v(n);
	readv(v);
	vector<bool> dp(n+1,false);
	dp[n]=true;
	for(int i=n-1;i>=0;i--){
		int right=i+v[i]+1;
		int left=i-v[i]-1;
		
		// cout<<i<<" : {"<<left<<" , "<<right<<" }\n";
		if(right<=n && dp[right]){
			dp[i]=true;
		}
		if(dp[i+1]){
			if(left+1>=0){
				dp[left+1]=true;
			}
		}
	}
	// F(i,0,n+1){
	// 	cout<<dp[i]<<" ";
	// }
	// cout<<endl;
	bool res=dp[0];
	YESNO1(res);
	return;
	// print answers here

}
