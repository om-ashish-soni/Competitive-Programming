// problem link : https://codeforces.com/problemset/problem/1671/D
// solution : below code

void solve(int t){
	int n;cin>>n;
	int x;cin>>x;
	int arr[n];
	scan(arr,n);
	int mn=*min_element(ALLA(arr,n));
	int mx=*max_element(ALLA(arr,n));
	int first,last;
	if(mn<=1) first=0;
	else{
		first=abs(arr[0]-1);
		first=min(first,abs(2*(mn-1)));
		first=min(first,abs(arr[n-1]-1));
	}
	if(mx>=x) last=0;
	else{
		last=abs(arr[n-1]-x);
		last=min(last,abs(2*(mx-x)));
		last=min(last,abs(arr[0]-x));
	}
	int sm=0;
	F(i,0,n-1){
		sm+=abs(arr[i+1]-arr[i]);
	}
	// printKickStartCase(t);
	int ans=sm+first+last;
	cout<<ans<<endl;
}
