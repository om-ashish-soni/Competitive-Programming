// problem link : https://codeforces.com/contest/61/problem/E
// solution : below code
void solve(){
	int n;cin>>n;vector<pair<int,int>> v(n);
	int arr[n];
	for(int i=0;i<n;i++){
		cin>>v[i].first;
		v[i].second=i;
	}
	sort(begin(v), end(v));
	for(int i=0;i<n;i++){
		arr[v[i].second]=i+1;
	}
	fenwickTree fn1=*new fenwickTree(n+2);
	fenwickTree fn2=*new fenwickTree(n+2);
	fn2.update(arr[n-1],1);
	for(int i=0;i<n-1;i++){
		fn1.update(arr[i],1);
	}
	int score=0;
	for(int i=n-2;i>0;i--){
		fn1.update(arr[i],-1);
		score+=(fn1.get(n)-fn1.get(arr[i]))*(fn2.get(arr[i]));
		fn2.update(arr[i],1);
	}
	cout<<score<<endl;
}
