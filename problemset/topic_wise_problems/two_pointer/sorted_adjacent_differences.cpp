// problem link : https://codeforces.com/problemset/problem/1339/B
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n,x;
	read(n);
	int a[n];
	read(a,n);
	SORTA(a,n);
	int l=0,r=n-1;
	vi v(n);
	F(i,0,n){
		if(i%2 == 0){
			// print(a[l]);l++;
			v[i]=a[l];l++;
		}else{
			// print(a[r]);r--;
			v[i]=a[r];r--;
		}
	}
	// println("");
	reverse(ALL(v));
	printv(v);
}
