// problem link : https://www.codechef.com/START20B/problems/BRTXORS
// solution : below code

int power(long long x, unsigned int y, int p) 
{ 
    int res = 1; 
    x = x % p; // Update x if it is more than or 
    if (x == 0) return 0; // In case x is divisible by p;
    while (y > 0) { 
        if (y & 1) res = (res*x) % p; 
        y = y>>1; // y = y/2 
        x = (x*x) % p; 
    } 
    return res; 
} 
int near(int n){
    int mod=1e9 + 7;
    double lg=log2(n);
    if(ceil(lg)==floor(lg)) return (power(2,ceil(lg)+1,mod)-1 + mod)%mod;
    return power(2,ceil(lg),mod)%mod;
}
void solve(int t){
	
	int n;
	cin>>n;
	if(n<3){
		cout<<n<<endl;

	}else{
		cout<<near(n)<<endl;
	}
	//utility
	// printKickStartCase(t);
	// print answers here
	// cout<<ctr<<endl;
}
