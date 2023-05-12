// problem link : https://codeforces.com/problemset/problem/1328/C
// solution : below code
// time taken : 8 m 11 s
void solve(int t){
	//shree ganeshay namah
	int n;
	string s;
	read(n);
	read(s);
	int index=n;
	string a,b;
	F(i,0,n) a+='0';
	F(i,0,n) b+='0';
	F(i,0,n){
		if(s[i]=='1'){
			index=i;
			a[i]='1';
			break;
		}
	}
	for(int i=0;i<index;i++){
		if(s[i]=='2'){
			a[i]=b[i]='1';
		}
	}
	F(i,index+1,n){
		b[i]=s[i];
	}
	println(a);
	println(b);
}
