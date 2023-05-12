// problem link : https://codeforces.com/contest/1688/problem/B
// solution : below code

int reduct(int n){
	int org=n;
	int pw=0;
	while(n%2==0){
		n>>=1;
		pw++;
	}
	// cout<<"num : "<<org<<" "<<"reduct : "<<pw<<endl;
	return pw;
}
void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int a[n];
	read(a,n);
	int even=0,odd=0;
	int pw=LLONG_MAX;
	F(i,0,n){
		if(a[i] & 1) odd++;
		else even++;
		int tmp=reduct(a[i]);
		pw=min(pw,tmp);
	}
	if(pw>0) even--;
	int ans=pw+even;
	println(ans);
}
