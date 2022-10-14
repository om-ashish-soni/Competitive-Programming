// problem link : https://codeforces.com/contest/1741/problem/Cint sum_partition(vi & v,int key){
	int sm=0;
	int last=-1;
	int mx=0;
	int n=v.size();
	F(i,0,n){
		sm+=v[i];
		if(sm>key) return LLONG_MAX;
		if(sm==key){
			int window=i-last;
			mx=max(mx,window);
			sm=0;
			last=i;
		}
	}
	if(sm>0) return LLONG_MAX;
	return mx;
}
void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int n;
	read(n);
	vi v(n);
	readv(v);
	int sm=0;
	int mn=LLONG_MAX;
	F(i,0,n){
		sm+=v[i];
		int part=sum_partition(v,sm);
		if(part != -1) mn=min(mn,part);	
	}
	println(mn);

	// print answers here

		

}
// solution : below code

