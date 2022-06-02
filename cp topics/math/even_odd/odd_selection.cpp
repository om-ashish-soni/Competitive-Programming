// problem link : https://codeforces.com/problemset/problem/1363/A
// solution : below code
// time taken : 22 m 37 s

void solve(int t){
	//shree ganeshay namah
	int n,x;
	cin>>n>>x;
	int arr[n];
	read(arr,n);
	int odd=0,even=0;
	F(i,0,n){
		if(arr[i]%2 == 1) odd++;
		else even++;
	}
	if(odd==0) YESNO2(false);
	else{
		odd--;
		x--;
		int cap=(odd/2)*2;
		if(x%2==0) x=max(0LL,x-cap);
		else x=max(1LL,x-cap);
		x-=even;
		if(x<=0) YESNO2(true);
		else{
			YESNO2(false);
		}
	}

}
