// problem link : https://codeforces.com/problemset/problem/1364/A
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n,x;
	read(n,x);
	int a[n];
	read(a,n);
	int sm=0;
	F(i,0,n) sm+=a[i];
	if(sm%x==0){
		int l=-1,r=-1;
		F(i,0,n){
			if(a[i]%x){
				l=i;
				break;
			}
		}
		FND(i,n-1,0){
			if(a[i]%x){
				r=i;
				break;
			}
		}
		// cout<<"l "<<l<<" , r: "<<r<<endl;
		int ans=-1;
		if(l!=-1) ans=max(ans,n-1-l);
		if(r!=-1) ans=max(ans,r);
		cout<<ans<<endl;
	}else{
		cout<<n<<endl;
	}
}
