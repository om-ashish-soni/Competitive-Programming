// problem link : https://codeforces.com/problemset/problem/1365/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a[n],b[n];
	read(a,n);
	read(b,n);
	vi hash(n+10,-1);
	vi v(n+10,0);
	F(i,0,n){
		hash[b[i]]=i;
	}
	F(i,0,n){
		int diff=i-hash[a[i]];
		int key=(diff+n)%n;
		v[key]++;
	}
	int mx=0;
	F(i,0,n+10){
		mx=max(mx,v[i]);
	}
	println(mx);
}
