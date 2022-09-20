// problem link : https://codeforces.com/problemset/problem/1710/A
// solution : below code

bool trythis(vi & v,int n,int m){
	// cout<<"n : "<<n<<" , m : "<<m<<endl;
	int sz=v.size();
	int ctr=0;
	if(n%2){
		
		int index=0;
		F(i,0,sz){
			// cout<<v[i]<<" , "<<(v[i]%(3*m))<<" , "<<(v[i]%(3*m))%(2*m)<<endl;
			if(v[i]>=3*m){
				if((v[i]-3*m)%(2*m)==0){
					index=i;
					break;
				}
			}else break;
		}
		if(v[index]<3*m) return false;
		ctr+=3;
		// cout<<"index : "<<index<<endl;
		v[index]-=3*m;
		F(i,0,sz){
			if(v[i]>=2*m) ctr+=(v[i]/m);
		}
		v[index]+=3*m;
	}else{
		F(i,0,sz){
			if(v[i]>=2*m) ctr+=(v[i]/(m));
		}
	}
	// cout<<"ctr : "<<ctr<<endl;
	return ctr>=n;
}
void solve(int t){
	//shree ganeshay namah
	int n,m,k;
	read(n,m);
	read(k);
	vi v(k);
	readv(v);
	SORT(v);
	REVERSE(v);
	// printv(v);
	bool first=trythis(v,n,m);
	bool second=trythis(v,m,n);
	if(first || second){
		YESNO2(true);
	}else{
		YESNO2(false);
	}
	// print answers here


}
