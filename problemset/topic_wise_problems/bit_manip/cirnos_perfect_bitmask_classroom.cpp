// problem link : https://codeforces.com/contest/1688/problem/A
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	bitset<64> bs(n);
	int m=0,one=0;
	if(n==1){
		cout<<3<<endl;
		return;
	}
	vector<int> match;
	F(i,0,64){
		if(bs[i]==1){
			match.pb(i);
		}
	}

	int ans=(1LL<<match.front());
	if(match.size()>1){
		cout<<ans<<endl;
		return;
	}else{
		cout<<ans+1<<endl;
		return;
	}
}
