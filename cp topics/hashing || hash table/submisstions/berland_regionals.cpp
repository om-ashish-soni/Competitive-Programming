// problem link : https://codeforces.com/problemset/problem/1519/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi a(n),b(n);
	readv(a);
	readv(b);
	vi v(n,0);
	map<int,vi> mp;
	F(i,0,n){
		mp[a[i]].pb(b[i]);
	}
	FEACH(pr,mp){
		vi & row=pr.second;
		SORT(row);
		REVERSE(row);
		int sz=row.size();
		F(i,1,sz){
			row[i]+=row[i-1];
		}
		REVERSE(row);
		F(i,1,sz+1){
			int mod=(sz%i);
			v[i-1]+=row[mod];
		}
	}
	printv(v);


	// print answers here

}
