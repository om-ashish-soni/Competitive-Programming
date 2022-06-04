// problem link : https://codeforces.com/problemset/problem/977/C
// solution : below code


void solve(int t){
	//shree ganeshay namah
	int n,k;
	read(n,k);
	int a[n];
	read(a,n);
	SORTA(a,n);
	if(k==0){
		if(a[0]==1) return reject();
		else{
			cout<<1LL<<endl;
			return ;
		}
	}
	if(k==n){
		println(a[n-1]);
	}else{
		if(a[k]==a[k-1]) return reject();
		else{
			println(a[k-1]);
		}
	}
}
