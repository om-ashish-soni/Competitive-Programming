// problem link : https://codeforces.com/problemset/problem/1602/B
// solution : below code

void solve(int t){
		//shree ganeshay namah
		// println("shree ganeshay namah");
		int n;
		read(n);
		vvi v(2*n,vi(n));
		readv(v[0]);
		int limit=0;
		F(i,1,2*n){
			limit=i;
			map<int,int> mp;
			FEACH(num,v[i-1]){
				mp[num]++;
			}

			bool equal=true;
			F(j,0,n){
				v[i][j]=mp[v[i-1][j]];
				if(v[i][j] != v[i-1][j]) equal=false;
			}
			// printv(v[i]);
			if(equal) break;
		}
		int q;
		read(q);

		F(i,0,q){
			int a,b;
			read(a,b);
			a--;
			b=min(b,limit);

			// println(b,a);
			// printv(v[b]);
			println(v[b][a]);
		}

    

		// print answers here

	}
