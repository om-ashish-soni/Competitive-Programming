#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
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
	// cout<<v.size()<<endl;
	for(int i=n-1;i>=0;i--){
		print(v[i]);
	}
	// for(auto &row: v) print(row);
	// for(int i=v.size()-1;i>=0;i--){
	// 	std::vector<int>& row=v[i];
	// 	print(row);
	// }
}
int lcm(int a,int b){
	return (a*b)/(__gcd(a,b));
}
int gcd(int a,int b){
	return __gcd(a,b);
}
void print(bool b){
	if(b) cout<<"YES";
	else cout<<"NO";
	cout<<endl;
}
void print(pair<int,int>& pr){
	cout<<"{"<<pr.first<<","<<pr.second<<"} ";
}
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
int charSum(char a,char b){
	return a-48+b-48;
}
int twoscomp(int n){
	if(n==0) return 0;
	double low=log2(n);
	if(ceil(low)==floor(low)) return 0;
	else return pow(2,1+floor(low))-n;
}

int selectTwo(vector<int>& pref,int start){
	int ans=LLONG_MAX;
	if(start>-1) ans=min(ans,twoscomp(pref[pref.size()-1]-pref[start]));
	else ans=min(ans,twoscomp(pref[pref.size()-1]));
	for(int i=start+1;i<pref.size();i++){
		if(start != -1)ans=min(ans,twoscomp(pref[i]-pref[start])+twoscomp(pref[pref.size()-1]-pref[i]));
		else ans=min(ans,twoscomp(pref[i])+twoscomp(pref[pref.size()-1]-pref[i]));
	}
	return ans;
}
int selectThree(vector<int>& pref){
	int ans=LLONG_MAX;
	int self=0;
	ans=min(ans,selectTwo(pref,-1));
	for(int i=0;i<pref.size();i++){
		self=twoscomp(pref[i]);
		ans=min(ans,self+selectTwo(pref,i));
	}
	return ans;
}
void solve(){
	int n;
	cin>>n;
	unordered_map<int,int> hash;
	for(int i=0;i<n;i++){
		int num;
		cin>>num;
		hash[num]++;
	}
	vector<pair<int,int>> v;
	for(auto &pr:hash){
		v.push_back(pr);
	}
	sort(v.begin(), v.end());
	vector<int> freq;
	for(auto &pr:v){
		freq.push_back(pr.second);
	}
	vector<int> pref(freq.size());
	for(int i=0;i<freq.size();i++){
		if(i==0) pref[i]=freq[i];
		else pref[i]=pref[i-1]+freq[i];
	}

	// print(pref);


	int ans=LLONG_MAX;
	int m=v.size();
	ans=selectThree(pref);
	cout<<ans<<endl;
}

signed main(){
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	scanf("%lld",&t);
	while(t--){
		solve();
		// cout<<twoscomp(12)<<endl;
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
