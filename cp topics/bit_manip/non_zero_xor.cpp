// problem link : https://www.codechef.com/submit/NZXOR
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi v(n);
	readv(v);
	int key=0;
	map<int,int> mp;
	mp[0]++;
	int ctr=0;
	FEACH(num,v){
		key=(key ^ num);
		if(mp.count(key)){ 
			ctr++;
			mp.clear();
		}
		mp[key]++;
	}
	println(ctr);


	// print answers here

}
