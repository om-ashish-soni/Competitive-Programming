// problem link : https://www.codechef.com/START38B/problems/ANTIKNAPSACK
// solution : below code

void solve(int t){
	int n;int k;cin>>n>>k;
	int start=2;
	while(k%start==0){
		start++;
	}
	int num=start;
	for(int i=0;i<n;i++){
		cout<<num<<" ";
		num+=start;
	}
	cout<<endl;
}
