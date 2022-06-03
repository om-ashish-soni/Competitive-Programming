// problem link : https://codeforces.com/problemset/problem/1399/C
// solution : below code
// time taken : 29 m 51 s

int trythis(vi & a,vi & hsh,int key){
	int n=a.size();
	int score=0;
	vector<stack<int>> ump(110);
	FND(i,n-1,0) ump[a[i]].push(i);
	F(i,0,n){
		if(ump[a[i]].size()<=0) continue;
		if(ump[a[i]].top() != i) continue;
		ump[a[i]].pop();
		int rest=key-a[i];
		if(rest<0) continue;
		if(ump[rest].size()>0){
			ump[rest].pop();
			score++;
		}
	}
	return score;
}
void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi a(n);
	readv(a);
	vi hsh(110,0);
	F(i,0,n) hsh[a[i]]++;
	int mx=0;
	// print("n : ");println(n);
	// printv(a);
	F(i,1,110){
		int tmp=trythis(a,hsh,i);
		mx=max(mx,tmp);
	}
	println(mx);
}
