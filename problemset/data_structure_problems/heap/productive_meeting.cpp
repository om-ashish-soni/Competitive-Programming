// problem link : https://codeforces.com/problemset/problem/1579/D
// solution : below code


void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi v(n);
	readv(v);
	priority_queue<pii> pq;
	F(i,0,n){
		int num=v[i];
		if(num>0) pq.push({num,i});
	}
	vpii steps;
	while(pq.size()>1){
		pii first=pq.top();pq.pop();
		pii second=pq.top();pq.pop();
		// cout<<first.first<<" vs "<<second.first<<endl;
		first.first--;
		second.first--;

		steps.pb({first.second+1,second.second+1});
		if(first.first>0) pq.push(first);
		if(second.first>0) pq.push(second);
	}
	int sz=steps.size();
	println(sz);
	FEACH(pr,steps){
		println(pr.first,pr.second);
	}

	// print answers here

}
