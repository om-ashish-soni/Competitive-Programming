// problem link : https://codeforces.com/problemset/problem/1593/D1
// solution : below code


#define GCD(a,b) (__gcd((a),(b)))
void reject(){
	cout<<-1<<endl;
	return;
}
void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int n;
	read(n);
	vi v(n);
	readv(v);
	int mn=LLONG_MAX;
	F(i,0,n){
		mn=min(mn,v[i]);
	}
	int hcf=0;
	F(i,0,n){
		int diff=v[i]-mn;
		hcf=GCD(hcf,diff);
	}
	if(hcf==0) return reject();
	println(hcf);
	// print answers here

}
