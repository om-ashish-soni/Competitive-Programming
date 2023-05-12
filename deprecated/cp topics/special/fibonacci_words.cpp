// problem link : https://codeforces.com/problemset/problem/1505/C
// solution : below code

void solve(int t){
	//shree ganeshay namah
	// println("shree ganeshay namah");
	string s;
	read(s);
	int n=s.size();
	F(i,2,n){
		char a=s[i-2];
		char b=s[i-1];
		char c=(a-'A'+b-'A')%26+'A';
		// cout<<s[i]<<" vs "<<c<<endl;
		if(c != s[i]){
			YESNO1(false);return;
		}
	}

	YESNO1(true);
	// println(ctr);

	// print answers here

}
