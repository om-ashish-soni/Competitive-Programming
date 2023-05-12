// problem link : https://codeforces.com/problemset/problem/514/A
// solution : below code
// time taken : 5  m 32 s

void solve(int t){
	//shree ganeshay namah
	string s;read(s);
	if(s[0]=='9' || s[0]<='4') ;
	else s[0]='0'+'9'-s[0];
	int n=s.size();
	F(i,1,n){
		if(s[i]>'4'){
			s[i]='0'+('9'-s[i]);
		}
	}
	println(s);
}

