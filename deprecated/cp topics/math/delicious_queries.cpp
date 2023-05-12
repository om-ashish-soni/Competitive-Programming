// problem link : https://www.codechef.com/submit/DQUERY?tab=statement
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	vi v(n);
	readv(v);
	// printv(v);
	vi pref=v;
	F(i,1,n){
		pref[i]+=pref[i-1];
	}
	int q;
	read(q);
	vpii qs(q);
	set<int> myprime_set;
	F(i,0,q){
		int p,k;
		read(p,k);
		qs[i]={p,k};
		myprime_set.insert(p);
	}
	vi myprimes;
	FEACH(num,myprime_set) myprimes.pb(num);
	map<int,vi> mp;
	F(i,0,n){
		FEACH(num,myprimes){
			if(v[i]<num) break;
			if(v[i]%num==0){
				// cout<<v[i]<<" vs "<<num<<endl;
				mp[num].pb(i);
			}
		}
	}
	// printv(myprimes);
	map<int,vi> mp_diff;
	FEACH(pr,mp){
		vi & row=pr.second;
		vi vfirst;
		FEACH(index,row){
			vfirst.pb(v[index]);
		}
		vi vsecond=vfirst;
		SORT(vsecond);
		int sz=vfirst.size();
		REVERSE(vsecond);
		vi newrow(sz);
		newrow[0]=vsecond[0]-vfirst[0];
		F(i,1,sz){
			vfirst[i]+=vfirst[i-1];
			vsecond[i]+=vsecond[i-1];
			newrow[i]=vsecond[i]-vfirst[i];
		}
		// cout<<pr.first<<" : "<<endl;
		// printv(row);
		// printv(vfirst);
		// printv(vsecond);
		mp_diff[pr.first]=newrow;
	}
	F(i,0,q){
		// int p,k;
		// read(p,k);
		int p=qs[i].first;
		int k=qs[i].second;
		vi & row=mp[p];
		// printv(row);
		int index=lower_bound(ALL(row),k)-row.begin();
		index--;
		vi & newrow=mp_diff[p];
		int ans=pref[k-1];
		if(index>=0){
			// cout<<"p : "<<p<<" , k : "<<k<<" , index : "<<index<<" , addon : "<<newrow[index]<<endl;	
			ans+=newrow[index];
		}
		println(ans);
		//process

	}
	// print answers here

}
