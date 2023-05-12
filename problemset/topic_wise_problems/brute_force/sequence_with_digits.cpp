// problem link : https://codeforces.com/problemset/problem/1355/A
// solution : below code

int calcaddon(int n){
	int mx=0,mn=9;
	while(n){
		int digit=n%10;
		mx=max(mx,digit);
		mn=min(mn,digit);
		n/=10;
	}
	return mx*mn;
}
void solve(int t){
	//shree ganeshay namah
	int n,k;
	read(n,k);
	k--;
	while(k--){
		int addon=calcaddon(n);
		if(addon==0) break;
		n+=addon;
	}
	println(n);
}
