// problem link : https://codeforces.com/contest/1463/problem/B
// solution : below code

void solve(){
	int n;cin>>n;int arr[n];scan(arr,n);
	int b[n];
	int c[n];
 
	int db=0,dc=0,sm=0;
	for(int i=0;i<n;i++){
		if(i%2==0){
			b[i]=1;
			c[i]=arr[i];
		}else{
			c[i]=1;
			b[i]=arr[i];
		}
		db+=abs(b[i]-arr[i]);
		dc+=abs(c[i]-arr[i]);
		sm+=arr[i];
	}
	if(db*2 <= sm){
		print(b,n);
	}else{
		print(c,n);
	}
}
