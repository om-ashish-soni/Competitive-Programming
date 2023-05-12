// Problem link : https://codeforces.com/contest/459/problem/D
// Solution : below code 
void solve(){
	int n,q;cin>>n;int arr[n],pref[n],suff[n];
	unordered_map<int,int>hash;
	fenwickTree fs=*new fenwickTree(n+2);
	for(int i=0;i<n;i++){
		cin>>arr[i];
		hash[arr[i]]++;
		pref[i]=hash[arr[i]];
	}
	hash.clear();
	for(int i=n-1;i>=0;i--){
		hash[arr[i]]++;suff[i]=hash[arr[i]];
	}
    int score=0;
    fs.update(suff[n-1],1);
    for(int i=n-2;i>=0;i--){
    	score+=fs.get(pref[i]-1);
    	fs.update(suff[i],1);
    }
    cout<<score<<endl;
}
