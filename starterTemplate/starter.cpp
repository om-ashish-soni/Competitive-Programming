#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
// check timeout
void checkTimeout(){
	double tm=(float)clock()/CLOCKS_PER_SEC;
	if(tm>=2){
		cerr<<"Time limit exeeded"<<endl;
		exit(0);
	}
}
//factors 
void findAllFactors(int n,std::vector<int>& factors){
	double sqroot=sqrt(n);
	factors.push_back(1);
	for(int i=2;i<=sqroot;i++){
		if(n%i == 0){
			factors.push_back(i);
			if(n/i != i){
				factors.push_back(n/i);
			}
		}
	}
	factors.push_back(n);
	sort(factors.begin(),factors.end());
}
//lcm and gcd
int lcm(int a,int b){
	return (a*b)/(__gcd(a,b));
}
int gcd(int a,int b){
	return __gcd(a,b);
}
//printing modules
void print(int num){
	cout<<num<<endl;
}
void print(int *arr,int start,int end){
	for(int i=start;i<=end;i++){
		cout<<arr[i]<<" ";
	}cout<<endl;
}
void print(int *arr,int n){
	for(int i=0;i<n;i++){
		cout<<arr[i]<<" ";
	}cout<<endl;
}
void print(vector<pair<int,int>>& v){
	for(auto &pr:v){
		cout<<"{"<<pr.first<<","<<pr.second<<"}"<<endl;
	}
	cout<<endl;
}
void print(std::vector<int>& v){
	for(auto &num:v) cout<<num<<" ";cout<<endl;
}
void print(std::vector<string>& v){
	for(auto &num:v) cout<<num<<" ";cout<<endl;
}
void print(std::vector<std::vector<int>>& v,int n){
	for(int i=n-1;i>=0;i--){
		print(v[i]);
	}
}
void print(bool b){
	if(b) cout<<"YES";
	else cout<<"NO";
	cout<<endl;
}
void print(pair<int,int>& pr){
	cout<<"{"<<pr.first<<","<<pr.second<<"} ";
}

// modulo arithmetic 
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
int modMul(int a,int b,int mod){
	return ((a%mod)*(b%mod))%mod;
}
int modAdd(int a,int b,int mod){
	return ((a%mod)+(b%mod))%mod;
}
// fenwick tree
void update(int *BIT,int n,int x, int delta)
{
      for(; x <= n; x += x&-x)
        BIT[x] += delta;
}
int query(int *BIT,int x)
{
     int sum = 0;
     for(; x > 0; x -= x&-x)
        sum += BIT[x];
     return sum;
}

//lis
int lis(int *v,int n){
	vector<int> seq;
	for(int i=0;i<n;i++){
		int num=v[i];
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return seq.size();
}
int lis(vector<int>&v){
	int n=v.size();
	vector<int> seq;
	for(auto num:v){
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return seq.size();
}
//lis return type list
void lis(int *v,int n,vector<int>&seq){
	for(int i=0;i<n;i++){
		int num=v[i];
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return ;
}
void lis(vector<int>&v,vector<int>& seq){
	int n=v.size();
	for(auto num:v){
		auto found=upper_bound(seq.begin(), seq.end(),num);
		if(found==seq.end()) seq.push_back(num);
		else *found=num;
	}
	return;
}

// scanning modules
void scan(int *arr,int n){
	for(int i=0;i<n;i++) cin>>arr[i];
}
void scan(vector<int>& v,int n){
	for(int i=0;i<n;i++) cin>>v[i];
}
void scan(int *arr,int n,vector<int>& hash){
	for(int i=0;i<n;i++) {cin>>arr[i];hash[arr[i]]=i;}
}
void scan(vector<int>& v,int n,vector<int>& hash){
	for(int i=0;i<n;i++) {cin>>v[i];hash[v[i]]=i;}
}
void scan(int *arr,int n,unordered_map<int,int>& hash){
	for(int i=0;i<n;i++) {cin>>arr[i];hash[arr[i]]=i;}
}
void scan(vector<int>& v,int n,unordered_map<int,int>& hash){
	for(int i=0;i<n;i++) {cin>>v[i];hash[v[i]]=i;}
}
// primeDivisors return type number
int primeFactorsBig(int n){
	unordered_set<int> uns;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				uns.insert(p);
				n/=p;
			}else p++;
		}else{
			uns.insert(n);
			break;
		}
	}
	return uns.size();
}
// primeDivisors with return type vector

void primeFactorsBig(int n,map<int,int>& mp){
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				mp[p]++;
				n/=p;
			}else p++;
		}else{
			mp[n]++;
			break;
		}
	}
	return;
}
void primeFactorsBig(int n,vector<int>& v){
	unordered_set<int> uns;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				uns.insert(p);
				n/=p;
			}else p++;
		}else{
			uns.insert(n);
			break;
		}
	}
	v.resize(uns.size());
	int len=0;
	for(auto num:uns) v[len++]=num;
	sort(v.begin(), v.end());
	return;
}
// isPrime
bool isPrimeBig(int n){
	if(n==1) return false;
	int p=2;
	while(true){
		if(n>=p*p){
			if(n%p==0){
				return false;
				n/=p;
			}else p++;
		}else{
			return true;
			break;
		}
	}
	return false;
}
// sieve of erathosthens for prime
const int N=1e6;
vector<int32_t> highestPrime(1e6,0);
vector<int32_t> lowestPrime(1e6,0);
// vector<vector<int>> factorsOf(N);
bitset <N> nonPrimeSet;
void seive(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num+num;j<=N;j+=num){
				nonPrimeSet[j]=1;
			}
		}
	}
	
}
void seiveWithHPLP(){
	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
	for(int num=2;num*num<=N;num++){
		if(0==nonPrimeSet[num]){
			for(int j=num+num;j<=N;j+=num){
				nonPrimeSet[j]=1;
				if(lowestPrime[j]==0) lowestPrime[j]=num;
				highestPrime[j]=num;
			}
			highestPrime[num]=lowestPrime[num]=num;
		}
	}
}
// void seiveWithAllFactors(){
// 	nonPrimeSet[0]=nonPrimeSet[1]=1;
	
// 	for(int num=2;num<=N;num++){
// 		factorsOf[num].push_back(1);
// 		if(0==nonPrimeSet[num]){
// 			for(int j=num+num;j<=N;j+=num){
// 				factorsOf[j].push_back(num);
// 				nonPrimeSet[j]=1;
// 				if(lowestPrime[j]==0) lowestPrime[j]=num;
// 				highestPrime[j]=num;
// 			}
// 			highestPrime[num]=lowestPrime[num]=num;
// 		}else{
// 			for(int j=num+num;j<=N;j+=num){
// 				factorsOf[j].push_back(num);
// 			}
// 		}
// 		factorsOf[num].push_back(num);
// 	}
// }
bool isPrime(int n){
	if(n>1e6) return isPrimeBig(n);
	return 0==nonPrimeSet[n];
}
void primeFactors(int n,vector<int>&v){
	if(n<2) return;
	if(n>1e6) return primeFactorsBig(n,v);
	while(n>1){
		int prime_factor=highestPrime[n];
		while(n%prime_factor==0){
			n/=prime_factor;
			
		}
		v.push_back(prime_factor);
	}
}
void primeFactors(int n,map<int,int>& mp){
	if(n<2) return;
	if(n>1e6) return primeFactorsBig(n,mp);
	while(n>1){
		int prime_factor=highestPrime[n];
		while(n%prime_factor==0){
			n/=prime_factor;
			mp[prime_factor]++;
		}
	}
}

int primeFactors(int n){
	if(n<2) return 0;
	if(n>1e6) return primeFactorsBig(n);
	int noOfPrimeFactors=0;
	while(n>1){
		int prime_factor=highestPrime[n];
		while(n%prime_factor==0){
			n/=prime_factor;
			noOfPrimeFactors++;
		}
	}
	return noOfPrimeFactors;
}
// roundOf
int roundOf(int n){
	return (int)pow(2,floor(log2(n)));
}
void solve(){
	// int n;
	// cin>>n;
	// int arr[n];
	// memset(arr,0,sizeof(arr));
	// memset(arr,-1,sizeof(arr));
	int n;
	cin>>n;
	cout<<n<<" : "<<isPrime(n)<<" lp : "<<lowestPrime[n]<<" , "<<"hp : "<<highestPrime[n]<<endl;
	// print(factorsOf[n]);
	// map<int,int> pf;
	// primeFactors(n,pf);
	// for(auto &pr:pf) { cout<<pr.first<<" : "<<pr.second<<endl;}
	// cout<<(pow(2,4)*pow(3,2)*pow(5,2))<<endl;
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
	seiveWithHPLP();
	// seiveWithAllFactors();
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
