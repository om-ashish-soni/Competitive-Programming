// problem link : https://codeforces.com/problemset/problem/1634/C
// Solution : below code

void solve(){
	int n,k;cin>>n>>k;
	if(n&1){
		if(k==1){
			print(true);
			for(int i=0;i<n;i++){
				cout<<i+1<<endl;
			}
		}else{
			return print(false);
		}
	}else{
		print(true);
		for(int i=0;i<n/2;i++){
			int init=2*i*k + 1;
			for(int j=0;j<k;j++,init+=2) cout<<init<<" ";cout<<endl;
			init=2*i*k+2;
			for(int j=0;j<k;j++,init+=2) cout<<init<<" ";cout<<endl;
		}
	}
}
