// problem link : https://codeforces.com/problemset/problem/1551/B2
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int k;
	read(k);
	vi v(n);
	readv(v);
	vi color(n,0);
	map<int,vi> mp;
	
	F(i,0,n){
		mp[v[i]].pb(i);
	}
	int val=0;
	vi sprint;
	FEACH(pr,mp){
		vi & row=pr.second;
		int limit=min(k,(int)row.size());
		F(i,0,limit){
			val++;
			int index=row[i];
			sprint.pb(index);
			
			if(sprint.size()==k){
				val=0;
				FEACH(k,sprint){
					val++;
					color[k]=val;
				}
				val=0;
				sprint.clear();
			}
		}
	}
	if(sprint.size()==k){
		val=0;
		FEACH(k,sprint){
			val++;
			color[k]=val;
		}
		val=0;
		sprint.clear();
	}
	printv(color);

	// print answers here

}
