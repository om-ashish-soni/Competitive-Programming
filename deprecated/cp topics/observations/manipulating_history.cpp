// problem link : https://codeforces.com/contest/1688/problem/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	n=2*n+1;
	vs v(n);
	unordered_map<char,int> ump;
	vc singles;
	F(i,0,n){
		read(v[i]);
		if(v[i].size()==1){
			singles.pb(v[i][0]);
		}
		FEACH(c,v[i]){
			ump[c]++;
		}
	}
	FEACH(c,singles){
		if(ump[c] % 2==1){
			println(c);return;
		}
	}

}
