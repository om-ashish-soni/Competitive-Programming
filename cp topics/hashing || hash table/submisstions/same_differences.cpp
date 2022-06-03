// problem link : https://codeforces.com/problemset/problem/1520/D
// solution : below code
// time taken : 5 m 11 s

void solve(int t){
	//shree ganeshay namah
	int n;read(n);
	int a[n];
	read(a,n);
	unordered_map<int,int> ump;
	F(i,0,n){
		ump[a[i]-(i+1)]++;
	}
	int ctr=0;
	FEACH(pr,ump){
		ctr+=(pr.second*(pr.second-1))/2;
	}

	println(ctr);

}
