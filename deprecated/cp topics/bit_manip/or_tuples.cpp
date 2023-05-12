// problem link : https://www.codechef.com/submit/ORTUPLES
// solution : below code

void solve(int t){
	//shree ganeshay namah
	vi v(3);
	readv(v);
	SORT(v);
	int key=(v[0] & v[1] & v[2]);
	bitset<32> bs(key);
	int ctr=bs.count();
	vi bits(32,0);
	FEACH(num,v){
		bitset<32> mybs(num);
		F(k,0,32){
			if(mybs[k]==1) bits[k]++;
		}
	}
	F(k,0,32){
		if(bits[k]==1){
			cout<<0<<endl;
			return;
		}
	}
	ctr*=2;
	int ans=(1LL<<ctr);
	println(ans);

	// print answers here

}
