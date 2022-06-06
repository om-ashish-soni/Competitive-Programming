// problem link : https://codeforces.com/problemset/problem/1691/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	int n;
	int k;
	read(n,k);
	string s;
	cin>>s;
	int ekam=0,dasak=0;
	FND(i,n-1,0){
		if(s[i]=='0') continue;
		int rem=n-1-i;
		// cout<<i<<" "<<rem<<" vs "<<k<<endl;
		if(rem<=k){
			// cout<<"swapping : "<<s[i]<<" "<<s[n-1]<<endl;
			k-=rem;
			swap(s[i],s[n-1]);
			ekam++;
			break;
		}
	}
	F(i,0,n-1){
		if(s[i]=='0') continue;
		int rem=i;
		if(rem<=k){
			k-=rem;
			swap(s[i],s[0]);
			dasak++;
			break;
		}
	}
	F(i,1,n-1){
		if(s[i]=='1'){
			ekam++;
			dasak++;
		}
	}
	// cout<<s<<" ";
	// cout<<dasak<<" "<<ekam<<endl;
	int ans=ekam + (dasak * 10LL);
	println(ans);
}
