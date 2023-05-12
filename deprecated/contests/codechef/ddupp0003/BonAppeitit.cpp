#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int setCustomers(vector<pair<int,int>>& row){
	int *low=(int*)calloc(row.size(),sizeof(int));
	int mx=0;
	for(int i=0;i<row.size();i++){
		int sum=0;
		for(int j=i-1;j>=0;j--){
			if(row[j].second<=row[i].first){
				low[i]=low[j];
				break;
			}
		}
		low[i]++;
		mx=max(mx,low[i]);
	}
	return mx;
}
void solve(){
	int n,k,f,s,r;
	cin>>n>>k;
	unordered_map<int,vector<pair<int,int>>> hash;
	for(int i=0;i<n;i++){
		scanf("%lld %lld %lld",&f,&s,&r);
		hash[r].push_back({f,s});
	}
	int sum=0;
	for(auto &pr:hash){
		sort(pr.second.begin(), pr.second.end());
		sum+=setCustomers(pr.second);
	}
	cout<<sum<<endl;
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
	}
	cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
	return 0;
}
