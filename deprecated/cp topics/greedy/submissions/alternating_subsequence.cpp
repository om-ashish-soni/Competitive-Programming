// problem link : https://codeforces.com/problemset/problem/1343/C
// solution : below code
// time taken : 4 m 17 s

void solve(int t){
	//shree ganeshay namah
	int n;
	cin>>n;
	int arr[n];
	read(arr,n);
	int sm=0;
	vi v;
	v.pb(arr[0]);
	F(i,0,n){
		if(v.back()>0 && arr[i]>0){
			v.back()=max(v.back(),arr[i]);
		}
		else if(v.back()<0 && arr[i]<0){
			v.back()=max(v.back(),arr[i]);
		}
		else{
			v.pb(arr[i]);
		}
	}
	FEACH(num,v){
		sm+=num;
	}
	println(sm);
}
