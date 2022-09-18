// problem link : https://codeforces.com/problemset/problem/1609/C
// solution : below code

// sieve of erathosthens for prime
const int N=1e6+10;
// vector<int> highestPrime(1e6+10,0);
// vector<int> lowestPrime(1e6,0);
vector<int> primes;
// vector<vector<int>> factorsOf(N+10);
bitset <N> nonPrimeSet;

void seiveWithAllPrimes(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num*num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	for(int num=2;num<=N;num++){
		if(0==nonPrimeSet[num]){
			primes.pb(num);
		}
	}
}

void solve(int t){
	//shree ganeshay namah
	int n;
	read(n);
	int k;
	read(k);
	vi v(n);
	readv(v);
	int ctr=0;
	F(i,0,n){
		if(nonPrimeSet[v[i]]==0){
			int left=0;
			int right=0;
			int l_i=i-k;
			int r_i=i+k;
			while(l_i>=0){
				if(v[l_i]==1){
					left++;
				}else break;
				l_i-=k;
			}
			while(r_i<n){
				if(v[r_i]==1){
					right++;
				}else break;
				r_i+=k;
			}
			int mul=(left+1)*(right+1)-1;
			ctr+=mul;
		}
	}
	println(ctr);
	//utility
	// printKickStartCase(t);
	// print answers here

}
