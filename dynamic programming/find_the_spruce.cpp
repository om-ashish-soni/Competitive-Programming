// problem link : https://codeforces.com/problemset/problem/1461/B
// solution : below code

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int n;
	read(n);
	int m;
	read(m);
	vvc mat(n,vc(m));
	readm(mat);
	vvi dp(n,vi(m,0));
	int key=0;
	int ctr=0;
	F(i,0,n){
		F(j,0,m){
			if(mat[i][j]=='*'){
				ctr++;
				dp[i][j]=1;
			}
		}
	}
	key=1;
	F(k,1,n){
		int last_key=key;
		key=last_key+2;
		F(i,k,n){
			vi pref(m,0);
			F(j,0,m){
				
				if(mat[i][j]=='*'){
					if(j-1>=0 && mat[i][j-1]=='*'){
						pref[j]=pref[j-1];
					}
					pref[j]++;
				}
			}
			// cout<<"key : "<<key<<" , i : "<<i<<endl;
			// cout<<"last_key : "<<last_key<<endl;
			// printv(pref);
			F(j,0,m){
				// cout<<"i-1 : "<<(i-1)<<" , j-key+1 : "<<(j-key+2)<<" : dp : "<<dp[i-1][j-key+2]<<endl;
				if(j-key+2>=0 && pref[j]>=key && dp[i-1][j-key+2]>=last_key){
					dp[i][j-key+1]=key;
					ctr++;

				}
			}
		}
	}
	// printm(dp);
	println(ctr);


	// print answers here
