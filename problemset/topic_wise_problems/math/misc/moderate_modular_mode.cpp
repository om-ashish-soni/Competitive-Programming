// problem link : https://codeforces.com/contest/1603/problem/B
// solution : below code

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	int a,b;
	read(a,b);
	if(a>b){
		cout<<a+b<<endl;
		return;
	}else{
		int mod=b%a;
		cout<<b-mod/2<<endl;
	}
	
	// printKickStartCase(t);	
	// print answers here
	

}
