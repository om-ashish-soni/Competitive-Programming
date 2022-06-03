// problem link : https://codeforces.com/problemset/problem/433/B
// solution : below code
// time taken : 9 m 2 s

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi a(n);
	readv(a);

	vi b=a;
	SORT(b);
	vi pa=a;
	vi pb=b;
	F(i,1,n){
		pa[i]+=pa[i-1];
	}
	F(i,1,n){
		pb[i]+=pb[i-1];
	}
	int m;
	read(m);
	F(i,0,m){
		int type,l,r;
		read(type,l,r);
		l--;r--;
		int ans=0;
		if(type==1){
			ans=pa[r]-pa[l]+a[l];
		}else{
			ans=pb[r]-pb[l]+b[l];
		}
		println(ans);
	}
}
