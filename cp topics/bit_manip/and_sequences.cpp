// problem link : https://codeforces.com/problemset/problem/1513/B
// solution : below code

#define MOD1 1000000007

int modMul(int a,int b,int mod){
	return ((a%mod)*(b%mod))%mod;
}

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi v(n);
	readv(v);
	int key=v[0];
	map<int,int> mp;
	F(i,0,n){
		mp[v[i]]++;
		key=(key & v[i]);
	}
	int freq=mp[key];
	int ctr=0;
	if(freq>1){
		ctr=modMul(freq,freq-1,MOD1);
		F(num,1,n-1){
			ctr=modMul(ctr,num,MOD1);
		}
	}
	println(ctr);
	// print answers here

}
