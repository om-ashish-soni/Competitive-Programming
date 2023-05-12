// problem link : https://codeforces.com/problemset/problem/1722/G
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int index=0;
	vi v;
	F(i,0,n-3) v.pb(++index);
	v.pb(1LL<<20);
	v.pb(1LL<<21);
	int xorr=0;
	FEACH(num,v){
		xorr=(xorr ^ num);
	}
	v.pb(xorr);
	printv(v);
	// print answers here
	

}
