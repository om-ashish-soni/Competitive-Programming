// problem link : https://codeforces.com/problemset/problem/489/B
// solution : below code
// time taken : 20 m 28 s
void solve(int t){
	//shree ganeshay namah
	int n;cin>>n;int a[n];
	F(i,0,n) cin>>a[i];
	int m;cin>>m;int b[m];
	F(i,0,m) cin>>b[i];
	sort(a,a+n);
	sort(b,b+m);
	int lb=0;
	int prs=0;
	F(i,0,n){
		// println(a[i],lb); 	
		for(int j=lb;j<m;j++){

			if(b[j]<a[i]-1){ 		
				lb=j;
			}
			if(a[i]-b[j]==1 || a[i]==b[j] || a[i]==b[j]-1){
				// println(i,j);
				lb=j+1;
				prs++;
				break;
			}
			if(a[i]+1<b[j]) break;
		}
	}
	println(prs);
}
