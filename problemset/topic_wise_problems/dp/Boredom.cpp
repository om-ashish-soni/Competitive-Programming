// problem link : https://codeforces.com/problemset/problem/455/A
// solution : below code


void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a[n];
	read(a,n);
	map<int,int> mp;
	F(i,0,n){
		mp[a[i]]++;
	}
	vpii v;
	v.pb({0,0});
	FEACH(pr,mp){
		v.pb(pr);
	}
	int sz=v.size();
	vi score(sz,0);
	score[0]=0;
	score[1]=v[1].first*v[1].second;
	F(i,2,sz){
		int addon=(v[i].first*v[i].second);
		if(v[i].first == v[i-1].first + 1){
			if(score[i-1]<score[i-2]+addon){
				score[i]=score[i-2]+addon;
			}else{
				score[i]=score[i-1];
			}
		}else{
			score[i]=score[i-1]+addon;
		}
	}	
	int mx=0;
	F(i,0,sz){
		mx=max(mx,score[i]);
	}
	println(mx);
}
