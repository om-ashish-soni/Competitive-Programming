// problem link : https://codeforces.com/problemset/problem/1515/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int m,x;
	read(m,x);
	vpii v(n);
	F(i,0,n){
		read(v[i].first);
		v[i].second=i;
	}
	SORT(v);
	REVERSE(v);
	priority_queue<pii> pq;
	F(i,0,m){
		pq.push({0,i+1});
	}
	vi color(n,0);
	vi scores(m,0);
	F(i,0,n){
		int key=v[i].first;
		int index=v[i].second;
		pii top=pq.top();pq.pop();
		top.first-=key;
		int group_index=top.second;
		scores[group_index-1]+=key;
		color[index]=group_index;
		pq.push(top);
	}
	// printv(scores);
	SORT(scores);
	int diff=scores.back()-scores.front();
	if(diff>x){
		YESNO1(false);
	}else{
		YESNO1(true);
		printv(color);
	}

	// print answers here

}
