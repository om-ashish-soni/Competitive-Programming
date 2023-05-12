// problem link : https://www.codechef.com/submit/MEANMEDIAN
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int a,b;
	read(a,b);
	vi v(3,0);
	v[1]=b;
	v[2]=b;
	v[0]=3*a-2*b;
	SORT(v);
	printv(v);

	// print answers here

}
