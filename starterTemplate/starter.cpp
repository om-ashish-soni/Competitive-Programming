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

int recurs(vector<int>& v,int sz,int i,vector<int>& memo){
	if(memo[i]) return memo[i];
	int sum=1;
	for(int j=i+1;j<sz;j++){
		if(v[i]<=v[j]){
			sum=max(sum,1+recurs(v,sz,j,memo));
		}
	}
	memo[i]=sum;
	return sum;
}
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
int lengthOfLIS(vector<int>& nums) {
        vector<int> memo;
        for(auto num:nums){
            auto found=lower_bound(memo.begin(),memo.end(),num);
            if(found==memo.end()) memo.push_back(num);
            else *found=num;
        }
        return memo.size();
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
void solve(){
	int n;
	cin>>n;
	int arr[n];
	vector<int> hash(n+1);
	vector<bool> tenfree(n+1,false);
	scan(arr,n,hash);
	int BIT[n+2];
	memset(BIT,0,sizeof(BIT));
	int mn=n;
	int ctr=1;
	while(mn>0){
		int dest=hash[ctr];
		// cout<<ctr<<" "<<dest<<endl;
		int upperFree=query(BIT,n)-query(BIT,ctr);
		if(upperFree>0){
			tenfree[ctr]=true;
		}
		// cout<<"upperFree : "<<upperFree<<endl;
		if(dest<mn){
			for(int i=dest+1;i<mn;i++){
				if(arr[i]<ctr) continue;
				update(BIT,n,arr[i],1);
				// cout<<"tenfree["<<arr[i]<<"] : true"<<endl;
				tenfree[arr[i]]=true;
			}
			mn=dest;
			//do some code here
		}
		
		ctr++;
	}
	for(int i=2;i<=n;i++){
		if(tenfree[i]);
		else return print(false);
	}
	return print(true);
}

signed main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("error.txt", "w", stderr);
    freopen("output.txt", "w", stdout);
#endif
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
