// problem link : https://codeforces.com/problemset/problem/1575/J
// solution : below code

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int n,m,k;
	read(n,m,k);
	vvi mat(n,vi(m));
	readm(mat);
	vi pos(k);
	readv(pos);
	int sz=(n+1)*m + 1000;
	disjointSet *ds=new disjointSet(sz);
	// printv(pos);
	vi op;
	F(i,0,k){
		int x=0;
		int y=pos[i]-1;
		// cout<<"x : "<<x<<" , y : "<<y<<endl;
		// int stopper=0;
		while(x<n){
			// cout<<"in loop => : "<<x<<" , "<<y<<endl;
			// if(stopper++>100) exit(0);

			int key=convert(x,y,m);
			key=ds->findSet(key);
			int next_key=key;
			if(mat[x][y] != 2){
				// cout<<"mat[x][y] : "<<mat[x][y]<<endl;
				if(mat[x][y]==1){
					next_key++;
				}else{
					next_key--;
				}
				mat[x][y]=2;
			}else{
				next_key+=m;				
				if(next_key<sz) ds->prefered_union(key,next_key);
			}
			
			key=next_key;
			x=key/m;
			y=key%m;
			

		}
		op.pb(y+1);
	}
	printv(op);
	delete ds;




	// printKickStartCase(t);	
	// print answers here
	

}
