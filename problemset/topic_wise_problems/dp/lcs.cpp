void solve(){
	string s,t;
	cin>>s>>t;
	int n=s.size(),m=t.size();
	int dp[n+1][m+1];
	s="-"+s;
	t="+"+t;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j]=0;
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i]==t[j]){
				dp[i][j]=1+dp[i-1][j-1];
			}else{
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}
	int i=n,j=m;
	string lcs;
	while(i>0 && j>0){
		if(s[i]==t[j]){
			lcs+=s[i];
			i--;j--;
		}else{
			if(dp[i-1][j]>dp[i][j-1]){
				i--;
			}else{
				j--;
			}
		}
	}
	reverse(lcs.begin(), lcs.end());
	cout<<lcs<<endl;
	// cout<<dp[n][m]<<endl;
}
