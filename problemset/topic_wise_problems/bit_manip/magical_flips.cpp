// problem link : https://www.codechef.com/START10B/problems/CRDFLP
// solution : below code

void solve(int t){
	int n;cin>>n;
	int a[n],b[n];
	scan(a,n);
	scan(b,n);
	vvpii v(n,vpii(32));
	vb flipped(n,false);
	vb isfix(n,false);
	F(i,0,n){
		bitset<32> bs(a[i]);
		F(k,0,32){
			if(bs[k]==1) v[i][k].first++;
		}
	}
	F(i,0,n){
		bitset<32> bs(b[i]);
		F(k,0,32){
			if(bs[k]==1) v[i][k].second++;
		}
	}
	int flips=0;
	bitset<32> bs;
	for(int k=31;k>=0;k--){
		int total_counts=0;
		vi rem,tofix;
		F(i,0,n){
			if(flipped[i]){
				if(v[i][k].second>0){
					total_counts++;
				}
			}else if(isfix[i]){
				if(v[i][k].first>0){
					total_counts++;
				}
			}else{
				if(v[i][k].first>0){
					total_counts++;
					if(v[i][k].second==0) tofix.pb(i);
				}else if(v[i][k].second>0){
					total_counts++;
					rem.pb(i);
					tofix.pb(i);
				}
			}
		}
		if(total_counts>=n){
			bs.set(k);
			FEACH(ind,rem) flipped[ind]=true;
			FEACH(ind,tofix) isfix[ind]=true;
		}
	}
	F(i,0,n) if(flipped[i]) flips++;
	cout<<bs.to_ullong()<<" "<<flips<<endl;
}
