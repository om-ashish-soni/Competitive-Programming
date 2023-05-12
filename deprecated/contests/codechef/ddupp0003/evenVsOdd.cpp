#include<bits/stdc++.h>
#define int long long 
#define endl "\n"
using namespace std;
const int mod=1e9 + 7;
void checkTimeout(){
	double tm=(float)clock()/CLOCKS_PER_SEC;
	if(tm>=2){
		cerr<<"Time limit exeeded"<<endl;
		exit(0);
	}
}
static bool comp(pair<int,int>& p1,pair<int,int>&p2){
	if(p1.second==p2.second) return p1.first<p2.first;
	return p1.second>p2.second;
}
void print(int *arr,int n){
	for(int i=0;i<n;i++) cout<<arr[i]<<" ";cout<<endl;
}
void print(vector<int>& v){
	for(auto num:v) cout<<num<<" ";cout<<endl;
}
void print(vector<pair<int,int>>& v){
	for(auto &pr:v){
		cout<<"{"<<pr.first<<","<<pr.second<<"}"<<endl;
	}
	cout<<endl;
}
int decode(int *arr,int n){
	int xorr=0;
	for(int i=0;i<n;i++) xorr=(xorr xor arr[i]);
	return xorr;
}
void rootToLeaf(vector<vector<int>>& actual,int n,int start,int dist,unordered_map<int,int>& delay){
	if(start>n) return;
	dist+=1;
	if(actual[start].size()==0) delay[dist]++;
	for(auto node:actual[start]){
		rootToLeaf(actual,n,node,dist,delay);
	}
	return;
}
void construct(vector<vector<int>>& v,int n,int start,int par,int dist,vector<int>& delay){
    if(start>n) return;
    dist+=1;
    if(start !=1 && v[start].size()==1) delay[dist]++;
    vector<int>& childs=v[start];
    for(auto child:childs){
        if(child == par) continue;
        construct(v,n,child,start,dist,delay);
    }
    return;
}
int DO(int n,int m,int i,int val,vector<vector<int>>& DP){
	if(i>n) return 0;
	if(val>m) return 0;
	// cout<<i<<" "<<val<<endl;
	if(i==n) return 1;
	if(DP[i][val] != -1) return DP[i][val];
	int sum=0;
	if(i%2 == 0){
		vector<int> v(val-1);
		int indx=0;
		for(int j=1;j<val;j++){
			v[indx]=DO(n,m,i+1,j,DP);
		}
		for(auto num1:v){
			for(auto num2:v){
				sum=(sum%mod+(num1*num2)%mod)%mod;
			}
		}
	}else{
		vector<int> v(m-val);
		int indx=0;
		for(int j=val+1;j<=m;j++){
			v[indx++]=DO(n,m,i+1,j,DP);
		}
		for(auto num1:v){
			for(auto num2:v){
				sum=(sum%mod+(num1*num2)%mod)%mod;
			}
		}
	}
	checkTimeout();
	DP[i][val]=sum;
	return sum;
}
static bool comp2(pair<int,int>&a,pair<int,int>&b){
	return a.second<b.second;
}
int rearrange(string &s){
	int low=0;
	int steps=0;
	int found=-1;
	while(low != -1){
	    
		found=s.find('1',found+1);
// 		cout<<"low : "<<low<<"  ::: "<<"found : "<<found<<endl;
		if(found<low || found>=s.size()) break;
		steps+=found-low;
		low++;
	}
// 	cout<<steps<<endl;
	return steps;
}
void solve(){
	int n;
	cin>>n;
	string s1,s2;
	for(int i=0;i<n;i++){
		int num;
		cin>>num;
		int bitAnd=(num&1);
		s1+=(bitAnd+48);
		s2+=((bitAnd xor 1)+48);

	}
// 	cout<<s1<<" "<<s2<<endl;
// 	int ans;
// 	ans=rearrange(s1);
	int ans=min(rearrange(s1),rearrange(s2));
	cout<<ans<<endl;
}
signed main(){
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
