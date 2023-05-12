// Problem link  : https://codeforces.com/problemset/problem/230/B
// Solution : below code

// sieve of erathosthens for prime
const int N=1e6;
vector<int> highestPrime(1e6+10,0);
vector<int> lowestPrime(1e6,0);
vector<int> primes;
// vector<vector<int>> factorsOf(N);
bitset <N> nonPrimeSet;
void seive(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	
}
void solve(){
	int n;cin>>n;
	double sqroot=sqrt(n);
	if(ceil(sqroot)==floor(sqroot)){
		return print(nonPrimeSet[ceil(sqroot)]==0);
	}
	return print(false);
}
signed main(){     
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	seive();
	// seiveWithHPLP();
	// seiveWithAllFactors();
	// seiveWithAllPrimes();
	// init();
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
