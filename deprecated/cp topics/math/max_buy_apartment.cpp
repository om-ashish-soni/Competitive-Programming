// problem link : https://codeforces.com/contest/854/problem/B
// solution : below code

void solve(int t){
    //shree ganeshay namah
    int x,y;
	cin>>x>>y;
	
	if(y==0 || y==x){
		cout<<0<<" "<<0<<endl;
		return;
	}
	int mod=x%3;
	x-=mod;
	int one=x/3;
	int two=2*one;
	int ans=0;
	int first=1;

	if(y<=one){
		ans=2*y;
	}else{
		// cout<<"one : "<<one<<endl;
		y-=one;
		int mn=min(y,mod);
		// cout<<"mn : "<<mn<<endl;
		y-=mn;
		two-=y;
		ans=two;
		if(mod==2 && mn==1){
			ans++;
		}
	}
	println(first,ans);
}  
