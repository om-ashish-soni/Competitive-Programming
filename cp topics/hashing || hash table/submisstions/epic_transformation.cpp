// problem link : https://codeforces.com/contest/1506/problem/D
// solution : below code

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int n;read(n);
	vi v(n);
	readv(v);
	map<int,int> mp;
	FEACH(num,v) mp[num]++;
	int ctr=0;
	FEACH(pr,mp){
		int rem=n-pr.second;
		if(rem<pr.second){
			ctr+=pr.second-rem;
		}
	}
	if(ctr==0 && n%2==1) ctr=1;
	println(ctr);
	// println(ctr);

	// print answers here

}
