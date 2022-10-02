// problem link : https://codeforces.com/problemset/problem/1462/Dint getcost(vi & v,int key,int start){
	int n=v.size();
	int window=0;
	int cost=0;
	int l=start;
	F(i,start,n){
		window+=v[i];
		if(window>key) return -1;
		if(window==key){
			int sz=i-start+1;
			cost+=sz-1;
			start=i+1;
			window=0;
		}
	}
	if(window != 0) return -1;
	return cost;
}

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int n;
	read(n);
	vi v(n);
	readv(v);
	int key=0;
	int mn=n-1;
	F(i,0,n){
		key+=v[i];
		int cost=getcost(v,key,i+1);
		// cout<<"i : "<<i<<" , key : "<<key<<" , cost : "<<cost<<endl;
		if(cost != -1){
			int curr=cost+i;
			mn=min(mn,curr);
		}
	}
	println(mn);

	// print answers here

}
// solution : below code

