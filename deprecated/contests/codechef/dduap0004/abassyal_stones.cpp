// problem link : https://www.codechef.com/DDUAP0004/problems/HACKME
// solution : belowcode

#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;

int stringHash(const string & s){
	int mx=0,mn=1000;
	char mx_element,mn_element;
	int mp[26];
	memset(mp,0,sizeof(mp));
	for(auto c:s) mp[c-'a']++;
	for(int i=0;i<26;i++){
		if(mp[i] == 0) continue;
		if(mp[i]> mx){
			mx=mp[i];
			mx_element='a'+i;
		}
		if(mp[i]<mn){
			mn=mp[i];
			mn_element='a'+i;
		}
	}
	return mx_element-mn_element;
}
void solve(){
	int n,k;string s;
	cin>>n>>k>>s;
	if(k==1){cout<<stringHash(s)<<endl;return;}
	int memo[n+1][k+1];
	for(int i=0;i<=n;i++) for(int j=0;j<=k;j++) memo[i][j]=LLONG_MAX;
	memo[n-1][0]=stringHash(s.substr(n-1));
	for(int i=n-2;i>=0;i--){
		string myStr;myStr+=s[i];
		int cost=LLONG_MAX;
		for(int index=i+1;index<n;index++){
			int mycost=stringHash(myStr);
			int limit=min(k-2,n-index-1);
			for(int j=0;j<=limit;j++){
				int tempCost=mycost+memo[index][j];
				cost=min(cost,tempCost);
				memo[i][j+1]=min(memo[i][j+1],tempCost);
			}
			myStr+=s[index];
		}
		memo[i][0]=stringHash(s.substr(i));
	}
	int mn_cost=LLONG_MAX;
	for(int i=0;i<k;i++) mn_cost=min(mn_cost,memo[0][i]);
	cout<<mn_cost<<endl;
}
signed main(){
	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int t;cin>>t;while(t--) solve();
	return 0;
}
