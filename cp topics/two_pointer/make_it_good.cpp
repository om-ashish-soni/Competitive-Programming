// problem link : https://codeforces.com/problemset/problem/1385/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n,x;
	read(n);
	int a[n];
	read(a,n);
	vi v(n,0);
	int peak=n-1;
	int r=n-1;
	int l=n-1;
	for(int i=n-2;i>=0;i--){
		if(a[i]>=a[i+1]){
			peak=i;
		}else break;
	}
	l=peak;
	for(int i=peak-1;i>=0;i--){
		if(a[i]<=a[i+1]){
			l=i;
		}else break;
	}
	println(l);
}
