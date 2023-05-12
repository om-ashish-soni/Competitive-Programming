// problem link : https://codeforces.com/problemset/problem/1353/D
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int n;
    read(n);
    priority_queue<pipii,vector<pipii>,greater<pipii>> pq;
	pq.push({(-n+1),{0,n-1}});
	vi v(n,0);
	int ctr=0;
	while(pq.size()>0){
		pipii top=pq.top();pq.pop();
		int l=top.second.first;
		int r=top.second.second;
		int mid=(l+r)/2;
		ctr++;
		v[mid]=ctr;
		if(l<mid){
			pq.push({l-(mid-1),{l,mid-1}});
		}
		if(mid<r){
			pq.push({mid+1-r,{mid+1,r}});
		}
	}
	printv(v);
}   
