// problem link : https://codeforces.com/contest/1733/problem/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi v(n);
	readv(v);
	int bit=v[0]%2;
	int key=-1;
	int key_index=-1;
	vpii steps;
	FND(i,n-1,0){
		if(bit==v[i]%2){
			if(key==-1){
				key=v[i];
				key_index=i;
			}else{
				v[i]=key;
				steps.pb({i+1,key_index+1});
			}
		}
	}
	F(i,0,n){
		if(bit != v[i]%2){
			v[i]=v[0];
			steps.pb({1,i+1});
		}
	}
	int sz=steps.size();
	println(sz);
	FEACH(pr,steps){
		println(pr);
	}
	// print answers here

}
