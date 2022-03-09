// problem link : https://codeforces.com/contest/380/problem/C
// solution : below code
// issue : time limit exceeded on testcase 13

#include<bits/stdc++.h>
#define int long long 
#define endl "\n"
using namespace std;
int dfs(vector<vector<int>>&v,vector<int>& score,int start){
	int ctr=2;
	for(auto node:v[start]){
		ctr+=dfs(v,score,node);
	}
	score[start]=ctr;
	return ctr;
}
int getScore(vector<vector<int>>& v,vector<int>&score,vector<int>&partner,int l,int r,int start){
	if(l>=partner[start] or r<=start){
		return 0;
	}
	// cout<<start<<" "<<partner[start]<<endl;
	// cout<<l<<","<<r<<" "<<start<<","<<partner[start]<<endl;
	if(l<=start && r>=partner[start]) return score[start];
	int total=0;
	
	vector<int>& row=v[start];
	int starting_index=upper_bound(begin(row), end(row),l)-row.begin();
	starting_index=max(starting_index-1,0LL);
	// if(starting_index<row.size()) cout<<"starting_index : "<<row[starting_index]<<endl;
	for(int i=starting_index;i<row.size();i++){
		if(row[i]>=r) break;
		total+=getScore(v,score,partner,l,r,row[i]);
	}
	// cout<<"l,r  : "<<l<<","<<r<<" "<<total<<endl;
	return total;
}
void solve(){
	string s;
	cin>>s;
	s=")"+s+"(";
	// cout<<s<<endl;
	int n=s.size();
	stack<pair<char,int>> st;
	vector<int> partner(n),score(n);
	for(int i=0;i<n;i++){
		score[i]=0;
		partner[i]=-1;
		if(s[i]==')'){
			if(st.empty()==false && st.top().first=='('){
				pair<char,int> pr=st.top();st.pop();
				partner[pr.second]=i;
			}	
		}else{
			st.push({s[i],i});
		}
		
	}
	partner[0]=n-1;
	vector<vector<int>> v(n);
	stack<int> highStack;
	highStack.push(0);
	for(int i=1;i<n;i++){
		if(partner[i]==-1) continue;
		while(partner[highStack.top()]<partner[i]){
			highStack.pop();
		}
		v[highStack.top()].push_back(i);
		highStack.push(i);
	}
	dfs(v,score,0);
	int m;cin>>m;
	for(int i=0;i<m;i++){
		int l,r;cin>>l>>r;
		// cout<<"l,r : "<<"{"<<l<<","<<r<<"}\n";
		int scr=getScore(v,score,partner,l,r,0);
		cout<<scr<<endl;
	}
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
	// cin>>t;
	while(t--){
		solve();
	}
}
