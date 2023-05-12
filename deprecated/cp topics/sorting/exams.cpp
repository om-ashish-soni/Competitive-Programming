// problem link : https://codeforces.com/problemset/problem/479/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vpii v(n);
	F(i,0,n){
		read(v[i].first);read(v[i].second);	
	}
	SORT(v);
	int mx=0;
	F(i,0,n){
		if(mx<=v[i].second){
			mx=v[i].second;
		}else mx=v[i].first;
	}
	println(mx);

}
