// problem link : https://codeforces.com/problemset/problem/1398/C
// solution : below code

void solve(int t){
	int n;
	cin>>n;
	string s;cin>>s;
	int sm=0;
	map<int,int> mp;
	for(int i=0;i<n;i++){
		sm+=(s[i]-'0');
		mp[sm-(i+1)]++;
	}
	int good=0;
	if(mp.count(0)) good+=mp[0];
	for(auto &pr:mp){
		// cout<<pr.first<<" : "<<pr.second<<" "<<(pr.second*(pr.second-1)/2)<<endl;
		good+=(pr.second*(pr.second-1))/2;
	}
	cout<<good<<endl;
}
