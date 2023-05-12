// problem link : https://codeforces.com/contest/1463/problem/A
// solution : below code

void solve(){
	int a,b,c;cin>>a>>b>>c;
	int mn=min(a,min(b,c));
	int total=a+b+c;
	return print((total%9==0)&&(mn>=total/9));
}
