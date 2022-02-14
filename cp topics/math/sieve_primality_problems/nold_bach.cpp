// Problem link : https://codeforces.com/problemset/problem/17/A
// Solution : below code

vector<int> myPref(1010,0);
vector<int> simpleV(1010,0);
void init(){
	int lenOfPrimes=primes.size();
	for(int i=0;i<lenOfPrimes-1;i++){
		int total=1+primes[i]+primes[i+1];
		if(total<1010){
			if(0==nonPrimeSet[total])simpleV[total]=1;
		}else break;
	}
	for(int i=1;i<1010;i++){
		myPref[i]=myPref[i-1]+simpleV[i];
	}
	// print(myPref);
}
bool isTakeTestCaseAsInput=false;
void solve(){
	int n,k;
	cin>>n>>k;
	return print(myPref[n]>=k);
}
signed main(){
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	// seive();
	// seiveWithHPLP();
	// seiveWithAllFactors();
	seiveWithAllPrimes();
	init();
	int t=1;
	if(isTakeTestCaseAsInput) cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
