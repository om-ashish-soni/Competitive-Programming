// problem link : https://codeforces.com/problemset/problem/1475/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int x,y,k;
	read(x,y,k);
	vi a(k),b(k);
	readv(a);
	readv(b);
	map<int,int> mp1,mp2;
	F(i,0,k){
		mp1[a[i]]++;
		mp2[b[i]]++;
	}
	int ctr=0;
	F(i,0,k){
		int addon=k-mp1[a[i]]-mp2[b[i]]+1;
		ctr+=addon;
	}
	ctr/=2;
	println(ctr);

	// print answers here

}
